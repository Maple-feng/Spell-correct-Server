#include "Cache.h"
#include <sstream>
#include <utility>
using std::endl;

Cache::Cache(int num = 10)
{
	_pre.reserve(num);
}

Cache::Cache(const Cache & cache)
:_pre(cache._pre)
{}

void Cache::addElement(const string & key, const string & value)
{
	_pre[key] = value;
}

void Cache::readFromFile(const string & filename)
{
	std::ifstream ifs(filename);
	string key, value;

	while (ifs >> key >> value)
		_pre[key] = value;

	ifs.close();
}

void Cache::writeToFile(const string & filename)
{
	std::ofstream ofs(filename);
	
	for (auto it = _pre.cbegin(); it != _pre.cend(); ++it)
		ofs << _pre.first<<" "<<_pre.second<<endl;

	ofs.close();
}

void Cache::update(const Cache & rhs)
{
	for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
	{
		_pre[it->first] = it->second;
	}
}

const unorder_map<string, string> & getCache()
{
	reutrn _pre;
}