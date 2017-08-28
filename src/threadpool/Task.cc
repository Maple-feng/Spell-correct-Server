#include "Task.h"
#include <sys/socket.h>

Task::Task(const string & query, int peerfd, Mydict dict)
:_query(query)
,_peerfd(peerfd)
,_inCache(false)
,_dict(dict)
{}

void Task::execute(Cache & cache)
{
	for (auto it = cache.getCache().cbegin(); it != cache.getCache().cend(); ++it)
	{
		if (_query == it->first) {
			::send(_peerfd, it->second.to_str(), it->second.size());
			return;
		}
	}

	queryIndex();
	reponse(cache);
}

void Task::queryIndex()
{
	auto tmpIndex = _dict.getIndex();
	for (int i = 0; i < _query.length(); ++i)
	{	
		for (auto it = tmpIndex.cbegin(); it != tmpIndex.cend(); ++it)
		{
			if (it->first = _query.substr(i, 1))
				calcu(it->second());
		}	
	}
}

void Task::calcu(set<int> & iset, int threshold)
{
	auto tmpDict = _dict.getDict();
	result tmpresult;
	for (auto it = iset.cbegin(); it != iset.cend(); ++it)
	{
		int dist = distance(tmpDict[*it].first);
		if (dist >= threshold)
		{
			tmpresult.frequency = tmpDict[*it].second;
			tmpresult.distance = dist;
			_resultQue.push(tmpresult);
		}
	}
}

int Task::distance(const string & rhs)
{
//	return lcs(_query, rhs);
	return shortest_Levenshtein_distance(_query, rhs);
}

void Task::reponse(Cache & cache)
{
	string res = _resultQue.top().query_word;
	cache.addElement(_query, res);
	::send(_peerfd, res.to_str(), res.size());
}