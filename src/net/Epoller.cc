#include "EpollPoller.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int createEpollfd()
{
	int fd = epoll_create1(0);
	if(-1 == fd)
	{
		perror("epoll_create1 error");
	}
	return fd;
}


void addEpollfd(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
		
	int ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl add error!");
		exit(EXIT_FAILURE);
	}
}

void delEpollfd(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
		
	int ret = epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl del error!");
		exit(EXIT_FAILURE);
	}
}


int acceptConnection(int listenfd)
{
	int connfd = ::accept(listenfd, NULL, NULL);
	if(-1 == connfd)
	{
		perror("accept error");
	}
	return connfd;
}

EpollPoller::EpollPoller(int listenfd)
: _efd(createEpollfd())
, _listenfd(listenfd)
, _isLooping(false)
, _events(1024)
{
	addEpollfd(_efd, listenfd);
}


void EpollPoller::loop()
{
	_isLooping = true;
	while(_isLooping)
	{
		waitEpollfd();
	}
}

void EpollPoller::unloop()
{
	if(_isLooping)
		_isLooping = false;
}


void EpollPoller::waitEpollfd()
{
	int nready;
	do
	{
		nready = epoll_wait(_efd, &*_events.begin(), _events.size(), 5000);
	}while(-1 == nready && errno == EINTR);

	if(-1 == nready)
	{
		perror("epoll_wait error!");
		exit(EXIT_FAILURE);
	}
	else if(0 == nready)
	{
		printf("epoll_wait timeout!\n");
	}

	if(nready == _events.size())
	{	
		_events.resize(nready * 2);
	}

	for(int idx = 0; idx != nready; ++idx)
	{
		//新连接的处理
		if(_events[idx].data.fd == _listenfd)
		{
			if(_events[idx].events & EPOLLIN)
			{
				handleConnection();
			}
		}
		else
		{	//旧连接的处理
			if(_events[idx].events & EPOLLIN)
				handleMessage(_events[idx].data.fd);
		}
	}
}

void EpollPoller::handleConnection()
{
	int connfd = acceptConnection(_listenfd);
	addEpollfd(_efd, connfd);

	TcpConnectionPtr conn(new TcpConnection(connfd));
	conn->setConnectionCallback(_onConnectionCb);
	conn->setMessageCallback(_onMessageCb);
	conn->setCloseCallback(_onCloseCb);

	_mapConnections.insert(std::make_pair(connfd, conn));
	conn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int connfd)
{
	auto iter = _mapConnections.find(connfd);
	if(iter != _mapConnections.end())
	{
		bool flag = isConnected(connfd);
		if(!flag)
		{	//处理客户端的数据  
			iter->second->handleMessageCallback();
		}
		else
		{   //连接断开的情况
			delEpollfd(_efd, connfd);
			iter->second->handleCloseCallback();
			_mapConnections.erase(iter);
		}
	}
}

bool EpollPoller::isConnected(int connfd)
{
	int nready;
	char buf[1024];
	do
	{
		nready = recv(connfd, buf, 1024, MSG_PEEK);
	}while(-1 == nready && errno == EINTR);

	return nready == 0;
}

void EpollPoller::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb = cb;
}
void EpollPoller::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb = cb;
}
void EpollPoller::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCb = cb;
}