#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "Cache.h"
#include "Mutexlock.h"
#include "Task.h"
#include "conf.h"
#include <vector>
#include <queue>
#include <functional>
using std::vector;
using std::queue;

class Thread;

class Threadpool
{
public:
	Threadpool(size_t threadNum, size_t buffSize);

	void start();
	void addTask(Task task);
	Task getTask();
	void cache_update(Config * cf);

	void threadFunc(Cache & cache);

private:
	MutexLock _mutex;
	Condition _add;
	Condition _take;

	size_t _threadNum;
	vector<Thread *> _threads;

	size_t _buffSize;
	queue<Task> _buffer;

	bool _isExit;
	Cache _cache;
};

#endif