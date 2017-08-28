 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-08-19 10:57:21
 ///

#ifndef __WANGDAO_NONCOPYABLE_H__
#define __WANGDAO_NONCOPYABLE_H__

namespace wd
{
	
class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

private:
	Noncopyable(const Noncopyable &);
	Noncopyable & operator=(const Noncopyable &);
};

}// end of namespace wd


#endif
