#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;

class Condition
: private Noncopyable
{
public:
	Condition(MutexLock& mutex);
	~Condition();
	void notify();
	void notifyall();
	void wait();
private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

#endif