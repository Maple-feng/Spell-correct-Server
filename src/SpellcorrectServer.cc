#include "SpellcorrectServer.h"
#include <ccypt>

SpellcorrectServer::SpellcorrectServer(const Config * cf)
:_tcpServer(cf->getConfigMap()[string("ip")], std::stoi(cf->getConfigMap()[string("port")])
,_threadPool(10, 20)
,_timerThread(5, 5, std::bind(&Threadpool.cache_update, _threadPool))
{}

void SpellcorrectServer::start()
{
	_tcpServer.start();
	_threadPool.start();
	_timerThread.start();
}

void SpellcorrectServer::setConnectionCallback(Callback cb)
{
	_tcpServer.setConnectionCallback(cb);
}

void SpellcorrectServer::setMessageCallback(Callback cb)
{
	_tcpServer.setMessageCallback(cb);
}

void SpellcorrectServer::setCloseCallback(Callback cb)
{
	_tcpServer.setCloseCallback(cb);
}