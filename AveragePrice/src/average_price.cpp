//============================================================================
// Name        : average_price.cpp
// Author      : Leon Zhao
// Version     : 0.1
// Copyright   : Initial
// Description : C++ Journey Begin, Wow!
//============================================================================


#include "mdWrapper.h"


int main() {
	std::cout << "C++ CTP Journey Begin, Wow!" << std::endl;
	std::shared_ptr<CmdWrapper> mdApi = std::make_shared<CmdWrapper>();
	mdApi->connect();

	return 0;
}
