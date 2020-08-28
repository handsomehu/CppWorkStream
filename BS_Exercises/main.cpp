#include <iostream>
#include "funcheader.h"
#include "lzpersons.h"
#include "twothread.h"
#include <thread>

int main()
{
    //nameage();
    //lzpersons pss{};
    //std::cin >> pss;
    //std::cout << pss;
    /*
    std::cout << "start the int vecot:" << std::endl;
    vecint();
    vecstr();
    writeint();
    readint();
    */
    TwoThread tt1;
    TwoThread tt2;
    std::thread h{&TwoThread::hello, &tt1};
    std::thread w{&TwoThread::world, &tt1};
    h.join();
    w.join();
    return 0;
}
