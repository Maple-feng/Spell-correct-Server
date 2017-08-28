#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <netinet/in.h>
#include <string>
using std::string;

class InetAddress
{
public:
	InetAddress(unsigned short port);
	InetAddress(const string & ip, unsigned short port);
	InetAddress(struct sockaddr_in addr);
	
	const struct sockaddr_in * getInetAddressPtr()const;

	string ip() const;
	unsigned short port() const;
private:
	struct sockaddr_in _addr;
};

#endif