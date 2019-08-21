//============================================================================
// Name        : average_price.cpp
// Author      : Leon Zhao
// Version     : 0.1
// Copyright   : Initial
// Description : C++ Journey Begin, Wow!
//============================================================================


#include "mdWrapper.h"


int main() {
	static int trycnt = 0;
	static bool loginOK = false;
	std::vector<char*> symbollist = {"rb1910","ru2001"};
	std::cout << "C++ CTP Journey Begin, Wow!" << std::endl;
	std::shared_ptr<CmdWrapper> mdApi = std::make_shared<CmdWrapper>();
	mdApi->connect();
	while(trycnt < 10)
	{
		loginOK = mdApi->getloginstatus();
		if (!loginOK)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			trycnt ++;
			std::cout <<"Tried to login times:";
			std::cout << trycnt <<std::endl;
		}
		else
			break;
	}

	if (loginOK)
	{
		mdApi->subscribe(symbollist);
		std::thread processqueue(&CmdWrapper::ProcessTaskFromQueue,mdApi);
		std::thread setfin(&CmdWrapper::SetComplete,mdApi);

		setfin.join();
		//mdApi->apijoin();  //will continue run if uncommented
							 //will terminate and have dump if commented out
		mdApi->apirelease();

	}
	else
		std::cout << "Cannot login to the system, please check!" << std::endl;

	return 0;
}
