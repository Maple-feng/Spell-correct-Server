#include "SocketIO.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

SocketIO::SocketIO(int fd)
: _fd(fd)
{}

size_t SocketIO::readn(char * buf, size_t count)
{
	size_t left = count;
	char * ptmp = buf;
	size_t total = 0;
	while(left > 0)
	{
		int ret = read(_fd, ptmp, left);
		if(-1 == ret)
		{
			if(errno == EINTR)
				continue;
			exit(EXIT_FAILURE);
		}
		else if(0 == ret)
		{	break;	}
		ptmp += ret;
		left -= ret;
	}
	return count - left;
}

size_t SocketIO::writen(const char * buf, size_t count)
{
	size_t left = count;
	const char * ptmp = buf;
	while(left > 0)
	{
		int ret = write(_fd, ptmp, left);
		if(-1 == ret)
		{
			if(errno == EINTR)
				continue;
			exit(EXIT_FAILURE);
		}
		ptmp += ret;
		left -= ret;
	}
	return count - left;
}

size_t SocketIO::recvPeek(char * buf, size_t count)
{	//预读取的操作
	size_t nread;
	do
	{
		nread = recv(_fd, buf, count, MSG_PEEK);
	}while(-1 == nread && errno == EINTR);
	return nread;
}

size_t SocketIO::readline(char * buf, size_t maxlen)
{
	size_t nleft = maxlen - 1;
	size_t total = 0;
	char * pbuf = buf;
	int nread;
	while(nleft > 0)
	{
		nread = recvPeek(pbuf, nleft);
		if(nread <= 0)
			return nread;

		for(int idx = 0; idx < nread; ++idx)
		{
			//找到了一行的标记
			if(pbuf[idx] == '\n')
			{
				size_t nsize = idx + 1;
				if(readn(pbuf, nsize) != nsize)
					return -1;
				pbuf += nsize;
				total += nsize;
				*pbuf = 0;
				return total;
			}
		}
		//没有找到'\n'
		if(readn(pbuf, nread) != nread)
			return -1;
		pbuf += nread;
		total += nread;
		nleft -= nread;
	}		
	*pbuf = 0;
	return maxlen - 1;
}