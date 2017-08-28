#include "dict.h"
#include "conf.h"

int main(int argc, char const *argv[])
{
	Config * pConf = Config.getInst("./config/conf");
	DictProducer * pDict = DictProducer.getInst(*pConf);

	pDict->bulid_dict();
	pDict->bulid_index();
	pDict->store_dict();
	pDict->store_index();

	DictProducer.destory();
	Config.destory();

	return 0;
}