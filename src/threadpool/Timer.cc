#include "Timer.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <poll.h>
#include <iostream>
using std::cout;
using std::endl;

int createTimerFd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(-1 == fd)
	{
		cout << "timerfd_create error" << endl;
	}
	return fd;
}


void setTimerFd(int fd, int initialTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;
	int ret = ::timerfd_settime(fd, 0, &value, NULL);
	if(-1 == ret)
	{
		cout << "timerfd_settime error!" << endl;
	}
}


void stopTimerFd(int fd)
{
	setTimerFd(fd, 0, 0);
}

void readTimerFd(int fd)
{
	uint64_t howmany = 0;
	int ret = ::read(fd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany))
	{
		cout << "read error!" << endl;
	}
}
	

Timer::Timer(int initialTime,
			 int intervalTime,
			 TimerCallback cb)
: _fd(createTimerFd())
, _intialTime(initialTime)
, _intervalTime(intervalTime)
, _isStarted(false)
, _cb(cb)
{
}


Timer::~Timer()
{
	if(_isStarted)
		stop();
}

//开启定时器
void Timer::start()
{
	setTimerFd(_fd, _intialTime, _intervalTime);
	_isStarted = true;

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	while(_isStarted)
	{
		int ret = ::poll(&pfd, 1, 5000);
		if(0 == ret)
		{
			cout << "poll timeout!" << endl;
			continue;
		}
		if(-1 == ret)
		{
			if(errno == EINTR)
				continue;
			cout << "poll error!" << endl;
			return;
		}

		if(pfd.revents & POLLIN)
		{
			readTimerFd(_fd);//处理定时器读事件，这一步不能少
			if(_cb)    //执行具体的任务
				_cb();
		}
	}
}


void Timer::stop()
{
	if(_isStarted)
	{
		stopTimerFd(_fd);
		_isStarted = false;
	}
}