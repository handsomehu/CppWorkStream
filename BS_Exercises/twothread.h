#ifndef TWOTHREAD_H
#define TWOTHREAD_H
#include <thread>
#include <mutex>
#include <unistd.h>
#include <chrono>
#include <iostream>

class TwoThread
{
public:
    TwoThread();
    void hello();
    void world();

private:
    std::mutex m;

};

#endif // TWOTHREAD_H
