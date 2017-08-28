#include "TcpServer.h"

TcpServer::TcpServer(unsigned short port)
: _addr(port)
, _serverSock()
, _epollPoller(_serverSock.fd())
{
}

TcpServer::TcpServer(const string & ip, unsigned short port)
: _addr(ip, port)
, _serverSock()
, _epollPoller(_serverSock.fd())
{
}

void TcpServer::start()
{
	_serverSock.ready(_addr);
	_epollPoller.setConnectionCallback(_onConnectionCb);
	_epollPoller.setMessageCallback(_onMessageCb);
	_epollPoller.setCloseCallback(_onCloseCb);

	_epollPoller.loop();
}

void TcpServer::stop()
{
	_epollPoller.unloop();
}