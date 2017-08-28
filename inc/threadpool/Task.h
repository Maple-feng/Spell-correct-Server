#ifndef __TASK_H__
#define __TASK_H__

#include "Cache.h"
#include "Mydict.h"
#include <queue>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::priority_queue;

struct result
{
	string query_word;
	int frequency;
	int distance;
};

bool cmp(const result & a, const result & b)
{
	if (a.distance != b.distance) 
		return a.distance > b.distance;
	if (a.frequency != b.frequency) 
		return a.frequency > b.frequency;
	if (a.query_word != b.query_word) 
		return a.query_word > b.query_word; 
}

class Task
{
public:
	Task(const string & query, int peerfd, Mydict dict);
	void execute(Cache & cache);

private:
	void queryIndex();
	void calcu(std::set<int> & iset, int threshold);
	int distance(const string & rhs);
	void response(Cache & cache);

private:
	string _query;
	int _peerfd;
	priority_queue<result, vector<result>, cmp> _resultQue;
	Mydict & _dict;
};

#endif