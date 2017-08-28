#include "TcpConnection.h"
#include <string.h>
#include <sstream>

TcpConnection::TcpConnection(int connfd)
: _sock(connfd)
, _sockIO(connfd)
, _localAddress(Socket::getLocalAddress(connfd))
, _peerAddress(Socket::getPeerAddress(connfd))
, _isShutdownWrite(false)
{

}

TcpConnection::~TcpConnection()
{
	if(_isShutdownWrite)
	{
		shutdown();
	}
}


string TcpConnection::receive()
{
	char buf[65536];
	memset(buf, 0, sizeof(buf));
	_sockIO.readline(buf, sizeof(buf));
	return string(buf);
}

void TcpConnection::send(const string & msg)
{
	_sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::shutdown()
{
	if(_isShutdownWrite)
	{
		_isShutdownWrite = true;
		_sock.shutdownWrite();
	}
}

int TcpConnection::fd()
{
	return _sock.fd();
}

string TcpConnection::toString()const
{
	std::ostringstream oss;
	oss << _localAddress.ip() << ":" << _localAddress.port() << "-->"
		<< _peerAddress.ip() << ":" << _peerAddress.port();
	return oss.str();
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb = cb;
}
void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb = cb;
}
void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCb = cb;
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnectionCb)
		_onConnectionCb(shared_from_this());
}
void TcpConnection::handleMessageCallback()
{
	if(_onMessageCb)
		_onMessageCb(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(_onCloseCb)
		_onCloseCb(shared_from_this());
}