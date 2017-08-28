#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>

Threadpool::Threadpool(size_t threadNum, size_t buffSize)
: _threadNum(threadNum)
, _buffSize(buffSize)
{
	_threads.reserve(_threadNum);
}

void Threadpool::start()
{
	for(size_t idx =0; idx != _threadNum; ++idx)
	{
		Thread * p = new Thread(
			std::bind(&Threadpool::threadFunc, this, std::placeholder::_1, _cache));
		p->start();
		_threads.push_back(p);
	}
} 

void Threadpool::addTask(Task task)
{
	MutexLockGuard lock(_mutex);
	while (_buffer.size() >= _buffSize)
		_add.wait();
	_buffer.push(task);
	_take.notify();
}

Task Threadpool::getTask()
{
	MutexLockGuard lock(_mutex);
	while (_buffer.empty()) _take.wait();
	Task tmp = _buffer.front();
	_buffer.pop();
	_add.notify();
	return tmp;
}

void Threadpool::cache_update(Config * cf)
{
	for (auto it = _threads.cbegin(); it != _threads.cend(); ++it)
	{
		_cache.update((*it)->getCache());
	}

	for (auto it = _threads.cbegin(); it != _threads.cend(); ++it)
	{
		(*it)->getCache().update(_cache);
	}	

	_cache.writeToFile(cf->getConfigMap()[string("cachePath")]);
}

void Threadpool::threadFunc(Cache & cahce)
{
	getTask().execute(cahce);
}