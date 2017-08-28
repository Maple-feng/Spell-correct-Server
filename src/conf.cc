#include "conf.h"
#include <fstream>
#include <sstream>

Config * Config::getInst(const char * filepath)
{
	if (_pConfig == nullptr)
	{
		_pConfig = new Config(filepath);
	}
	return _pConfig;
}

void Config::destory()
{
	if (_pConfig != nullptr)
		delete _pConfig;
}

Config::Config(const char * filepath)
:_filepath(filepath)
{}

map<string, string> & Config::getConfigMap()
{
	std::ifstream ifs(_filepath);
	string key, value;
	string text;
	while (std::getline(ifs, text))
	{
		std::istringstream line(text);
		line >> key;
		line >> value;
		_configMap[key] = value;
	}
	return _configMap;
}