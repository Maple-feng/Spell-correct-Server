#ifndef __SPELL_SERVER_H__
#define __SPELL_SERVER_H__

#include "conf.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include "TimerThread.h"

class SpellcorrectServer
{
public:
	typedef TcpServer::TcpServerCallback Callback;

	SpellcorrectServer(const Config * cf);
	void start();
	void setConnectionCallback(Callback cb);
	void setMessageCallback(Callback cb, Threadpool * tp);
	void setCloseCallback(Callback cb);
	Threadpool * getThreadpool() { return &_threadPool; }

private:
	TcpServer _tcpServer;
	Threadpool _threadPool;
	TimerThread _timerThread;
};

#endif