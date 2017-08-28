#ifndef __SOCKET_H__
#define __SOCKET_H__

class InetAddress;

class Socket 
{
public:
	Socket();
	Socket(int fd);
	void ready(const InetAddress & addr);
	int accept();

	void shutdownWrite();

	int fd();

	static InetAddress getLocalAddress(int fd);
	static InetAddress getPeerAddress(int fd);

private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind(const InetAddress & addr);
	void listen();
private:
	int _fd;
};

#endif