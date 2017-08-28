#ifndef __TIME_H__
#define __TIME_H__ 

#include "Noncopyable.h"

#include <iostream>
#include <functional>
using std::cout;
using std::endl;

class Timer
: private Noncopyable
{
public:
	typedef std::function<void()> TimerCallback;

	Timer(int initialTime,
		  int intervalTime,
		  TimerCallback cb);
	~Timer();

	void start();
	void stop();

private:
	int _fd;
	int _intialTime;
	int _intervalTime;
	bool _isStarted;
	TimerCallback _cb;
};

#endif