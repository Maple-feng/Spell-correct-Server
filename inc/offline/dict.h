#ifndef __DICT_H__
#define __DICT_H__

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <set>
using std::vector;
using std::string;
using std::map;
using std::pair;
using std::set;

class Config;

class DictProducer
{
public:
	static DictProducer * getInst(Config & cf);
	static void destory();

	void build_dict();
	void build_index();
	void store_dict(const char * filePath);
	void store_index(const char * indexPath);
	
	//debug
	void show_files() const;
	void show_dict() const;

private:
	DictProducer(Config & cf);
	DictProducer(Config & cf, SplitTool * splitTool);

	string get_fpath();
	void push_dict(string & word);

private:
	static DictProducer * _pDict;

	Config & _cf;
	vector<string> _corpus;

	map<string, int> _dict;
	vector<pair<string, int>> _data;
	map<string, set<int>> _index;
	int _data_index;
};

#endif