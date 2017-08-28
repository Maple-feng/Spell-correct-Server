#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include "InetAddress.h"
#include "Socket.h"
#include "EpollPoller.h"

class TcpServer
{
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;
public:
	TcpServer(unsigned short port);
	TcpServer(const string & ip, unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb)
	{	_onConnectionCb = cb;	}

	void setMessageCallback(TcpServerCallback cb)
	{	_onMessageCb = cb;	}

	void setCloseCallback(TcpServerCallback cb)
	{	_onCloseCb = cb;	}
private:
	InetAddress _addr;
	Socket _serverSock;
	EpollPoller _epollPoller;
	
	TcpServerCallback _onConnectionCb;
	TcpServerCallback _onMessageCb;
	TcpServerCallback _onCloseCb;

};

#endif