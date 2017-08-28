#ifndef __CACHE_H__
#define __CACHE_H__

#include <unorder_map>
#include <string>
#include <fstream>
#include <vector>
using std::unorder_map;
using std::string;
using std::vector;

class Cache
{
public:
	Cache(int num = 10);
	Cache(const Cache & cache);
	void addElement(const string & key, const string & value);
	void readFromFile(const string & filename);
	void writeToFile(const string & filename);
	void update(const Cache & rhs);
	const unorder_map<string, string> & getCache();

private:
	unorder_map<string, string> _pre;
};

#endif