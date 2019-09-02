//============================================================================
// Name        : average_price.cpp
// Author      : Leon Zhao
// Version     : 0.1
// Copyright   : Initial
// Description : C++ Journey Begin, Wow!
//============================================================================


#include "mdWrapper.h"
/*
#include <limits.h>
#include <unistd.h>
std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}
*/
int main() {
	static int trycnt = 0;
	static bool loginOK = false;
	std::vector<char*> symbollist = {"rb1910","ru2001","T1912"};
	std::cout << "C++ CTP Journey Begin, Wow!" << std::endl;
	std::shared_ptr<CmdWrapper> mdApi = std::make_shared<CmdWrapper>();
	//std::cout << getexepath() << std::endl;
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
		std::thread printvwap(&CmdWrapper::persistvwap,mdApi);
		//void CmdWrapper::persistvwap()

		//setfin.join();
		mdApi->apijoin();  //will continue run if uncommented
							 //will terminate and have dump if commented out
		//mdApi->getavg() ;
		mdApi->apirelease();

	}
	else
		std::cout << "Cannot login to the system, please check!" << std::endl;

	/*
    nlohmann::json jtest;
    jtest["hello"] = "World";
    jtest["url"] = "github.com";
    std::ofstream file("key.json");
    file << jtest;
	 */
	return 0;
}
