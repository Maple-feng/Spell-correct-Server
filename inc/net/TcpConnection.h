#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <functional>
#include <memory>
using std::string;

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection 
: public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(const TcpConnectionPtr & conn)> 
			TcpConnectionCallback;
public:
	TcpConnection(int connfd);
	~TcpConnection();

	string receive();
	void send(const string & msg);
	void shutdown();

	string toString()const;
	int fd();

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

private:
	Socket _sock;
	SocketIO _sockIO;
	InetAddress _localAddress;
	InetAddress _peerAddress;
	bool _isShutdownWrite;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};

#endif