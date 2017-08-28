#include "InetAddress.h"

#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

InetAddress::InetAddress(unsigned short port)
{
	memset(&_addr, 0, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const string & ip, unsigned short port)
{
	memset(&_addr, 0, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(struct sockaddr_in addr)
: _addr(addr)
{}


const struct sockaddr_in * InetAddress::getInetAddressPtr()const
{
	return &_addr;
}

string InetAddress::ip() const
{
	return string(inet_ntoa(_addr.sin_addr));	
}
	
unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);
}