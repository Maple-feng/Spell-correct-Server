#ifndef __TIMER_THREAD_H__
#define __TIMER_THREAD_H__

#include "Thread.h"
#include "Timer.h"

class TimerThread
{
public:
	TimerThread(int initialTime, int intervalTime,
				Timer::TimerCallback cb)
	: _timer(initialTime, intervalTime, cb)
	, _thread(std::bind(&Timer::start, &_timer))
	{}

	void start()
	{
		_thread.start();
	}

	void stop()
	{
		_timer.stop();
		_thread.join();
	}

private:
	Timer _timer;
	Thread _thread;
};

#endif