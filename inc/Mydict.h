#ifndef __MYDICT_H__
#define __MYDICT_H__ 

#include <map>
#include <string>
#include <set>
#include <vector>
#include <utility>
using std::map;
using std::set;
using std::string;
using std::vector;
using std::pair;

class Mydict
{
public:
	static Mydict * getInst(const char * dictPath, const char * indexPath);
	const vector<pair<string, int>> & getDict() const;
	const map<int, set<int>> & getIndex() const;

private:
	Mydict(const char * dictPath, const char * indexPath);

private:
	Mydict * _pMydict;

	vector<pair<string, int>> _dict;
	map<string, set<int>> _index;
};

#endif