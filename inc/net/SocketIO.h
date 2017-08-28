#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <stdio.h>

class SocketIO 
{
public:
	SocketIO(int fd);

	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
	size_t readline(char * buf, size_t maxlen);
private:
	size_t recvPeek(char * buf, size_t count);

private:
	int _fd;
};

#endif