#include "dict.h"
#include "conf.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cctype>
#include <iostream>
#include <utility>
#include <algorithm>
using std::cout;
using std::endl;

DictProducer * DictProducer::getInst(Config & cf)
{
	if (_pDict == nullptr)
	{
		_pDict = new DictProducer(cf);
	}
	return _pDict;
}

void DictProducer::destory()
{
	if (_pDict != nullptr)
		delete _pDict;
}

DictProducer::DictProducer(Config & cf)
:_cf(cf)
,_splitTool(nullptr)
,_data_index(0)
{	
	string path = get_fpath();

	DIR * dp = ::opendir(path.c_cstr());
	struct dirent * entry;
	struct stat buf;
	while ((entry = ::readdir(dp)) != NULL)
	{
		::stat(entry->d_name, &buf);
		if (entry->d_name[0] != '.') {
			string file_path = path + string(entry->d_name);
			_corpus.push_back(file_path);
		} 
	}

	::closedir(dp);		
}

void DictProducer::build_dict()
{
	for (auto it = _corpus.cbegin(); it != _corpus.cend(); ++it)
	{
		std::ifstream ifs(*it);
		if(!ifs.good())
		{
			cout << "ifstream open error!" << endl;
			return;
		}

		string line;
		while (std::getline(ifs, line))
		{
			std::stringstream ss(line);
			string word;
			while (ss >> word)
				push_dict(word);
		}
	}
}

void DictProducer::build_index()
{
	for (auto it = _dict.cbegin(); it != _dict.cend(); ++it)
	{
		_data.push_back(std::make_pair(it->first, it->second));

		for (int i = 0; i < (it->first).length(); ++i)
		{
			_index[(it->first).substr(i, 1)].insert(data_index);
		}
		++data_index;		
	}
}

void DictProducer::store_dict(const char * filePath)
{
	std::ofstream ofs(filepath);
	if (!ofs.good())
	{
		cout<<"ofstream open error!"<<endl;
		return;
	}

	for (auto it = _dict.cbegin(); it != _dict.cend(); ++it)
	{
		ofs<<it->first<<" "<<it->second<<endl;
	}
}

void DictProducer::store_index(const char * indexPath)
{
	std::ofstream ofs(indexPath);
	if (!ofs.good())
	{
		cout<<"ofstream open error!"<<endl;
		return;
	}

	for (auto it = _index.cbegin(); it != _index.cend(); ++it)
	{
		cout<<it->first<<" ";
		for (auto iter = (it->second).cbegin(); iter != (it->second).cend(); ++iter)
		{
			cout<<*iter<<" ";
		}
		cout<<endl;
	}
}

void DictProducer::show_files() const
{
	for (auto it = _corpus.cbegin(); it != _corpus.cend(); ++it)
	{
		cout<<*it<<endl;
	}
}

void DictProducer::show_dict() const
{
	for (auto it = _data.cbegin(); it != _data.cend(); ++it)
	{
		cout<<(*it).first<<" "<<(*it).second<<endl;
	}
}

string DictProducer::get_fpath()
{
	return _cf.getConfigMap()[string("dict_path")];
}

void DictProducer::push_dict(string & word)
{
	int ch = word[0];
	if (!::isdigit(ch)) 
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower); 
		_dict[word]++;
	}
}