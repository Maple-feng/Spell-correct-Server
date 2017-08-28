#ifndef __THREAD_H__
#define __THREAD_H__ 

#include "Noncopyable.h"
#include "Cache.h"
#include <functional>

class Thread
: private Noncopyable
{
public:
	typedef std::function<void(Cache&)> ThreadCallback;

	explicit Thread(ThreadCallback cb, Cache cache);
	~Thread();

	void start();
	void join();
	void setThreadCallback(ThreadCallback cb);
	Cache & getCache();

private:
	static void * threadFunc(void *);

private:
	pthread_t _pthId;
	ThreadCallback _cb;
	Cache _cache;	
};

#endif