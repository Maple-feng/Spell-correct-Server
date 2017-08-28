#include "Mydict.h"
#include <fstream>
#include <sstream>
#include <utility>
using std::ifstream;

Mydict * Mydict::getInst(const char * dictPath, const char * indexPath)
{
	if (_pMydict == nullptr)
	{
		_pMydict = new Mydict(dictPath, indexPath);
	}
	return _pMydict;
}

Mydict::Mydict(const char * dictPath, const char * indexPath)
{
	ifstream ifs_d(dictPath);
	ifstream ifs_i(indexPath);

	string line;
	while (std::getline(ifs_d, line))
	{
		std::stringstream ss(line);
		string key, value;
		ss >> key >> value;
		_dict.push_back(std::make_pair(key, stoi(value)));
	}

	while (std::getline(ifs_i, line))
	{
		std::stringstream ss(line);
		string letter, num;
		set<int> index;
		ss >> letter;
		while (ss >> num) index.insert(stoi(num));
		_index[letter] = std::move(index);
	}
}

const vector<pair<string, int>> & Mydict::getDict() const
{
	return _dict;
}

const map<int, set<int>> & Mydict::getIndex() const
{
	return _index;
}