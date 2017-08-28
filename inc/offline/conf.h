#ifndef __CONF_H__
#define __CONF_H__

#include <map>
#include <string>
using std::map;
using std::string;

class Config
{
public:
	static Config * getInst(const char * filepath);
	static void destory();
	map<string, string> & getConfigMap();

private:
	Config(const char * filepath);

private:
	Config * _pConfig;

	string _filepath;
	map<string, string> _configMap;
};

#endif