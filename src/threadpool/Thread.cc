#include "Thread.h"

Thread::Thread(ThreadCallback cb, Cache cache)
: _pthId(0)
, _isRunning(false)
, _cb(cb)
,_cache(cache)  
{}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthId);
		_isRunning = false;
	}
}

void Thread::start()
{
	pthread_create(&_pthId, NULL, &Thread::threadFunc, this);
	_isRunning = true;
}

void Thread::join()
{
	if(_isRunning)
	{
		pthread_join(_pthId, NULL);
		_isRunning = false;
	}
}

void Thread::setThreadCallback(Thread::ThreadCallback cb)
{	_cb = cb;	}

Cache & Thread::getCache()
{
	return _cache;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pThread = static_cast<Thread *>(arg);
	if(pThread)
		pThread->_cb(pThread->_cache);
	return NULL;
}