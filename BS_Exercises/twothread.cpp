#include "twothread.h"

TwoThread::TwoThread()
{

}

void TwoThread::hello()
{
    //std::cout << "start H" << std::endl;
    while(true)
    {
        //std::unique_lock<std::mutex> lck {m};
        std::cout << "Hello" ;
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "after hello" ;
        std::cout << std::flush;
    }
}
void TwoThread::world()
{

    //std::cout << "start W" << std::endl;
    while(true)
    {
        //std::unique_lock<std::mutex> lck {m};
      std::cout << " world" ;
      std::cout << std::flush;
        //sleep(1);
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "after world!";
      std::cout << std::flush;
    }
}
