#ifndef __MUTEX_LOCK_H__
#define __MUTEX_LOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock
: private Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();

	pthread_mutex_t * getMutexPtr()
	{	return &_mutex;	}

private:
	pthread_mutex_t _mutex;
};


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLock & _mutex;
};

#endif