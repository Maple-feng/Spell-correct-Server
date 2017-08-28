#include "SpellcorrectServer.h"
#include "conf.h"
#include "Mydict.h"
#include "Task.h"
#include <iostream>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::string;

void onConnection(TcpConnectionPtr & conn);
void onMessage(TcpConnectionPtr & conn;);
void onClose(TcpConnectionPtr & conn);

Threadpool * tp = nullptr;

int main(int argc, char const *argv[])
{
	Config * pConf = Config.getInst("./config/conf");

	string dictPath = Mydict.getInst(pConf->getConfigMap()[string("dictPath")]);
	string indexPath = Mydict.getInst(pConf->getConfigMap()[string("indexPath")]);
	Mydict * dict = Mydict.getInst(dictPath.to_str(), indexPath.to_str());

	SpellCorrectServer server(pConf);

	tp = server.getThreadpool();

	server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);

	server.start();

	return 0;
}

void onConnection(TcpConnectionPtr & conn)
{
	cout << conn->toString() << " has connected!" << endl;
	conn->send("welcome to server!");	
}

void onMessage(TcpConnectionPtr & conn)
{
	string query = conn->receive();
	int last = query.find('\n');
	if (last != string::npos) query = query.substr(0, n);

	cout<<"The query word is: "<<query<<endl;

	Task task(query, conn->fd(), *dict);
	tp->addTask(task);
}

void onClose(TcpConnectionPtr & conn)
{
	cout << conn->toString() << " has closed!" << endl;	
}