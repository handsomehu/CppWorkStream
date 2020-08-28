#include <iostream>
#include <thread>
#include <chrono>

void function1() {
   while (true) {
      std::cout << "Hi I'm the function 1" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Hi I'm the function 1 after sleeping" << std::endl;
   }
}

void function2() {
  while (true) {
     std::cout << "Hi I'm the function 2" << std::endl;
     std::this_thread::sleep_for(std::chrono::seconds(5));
     std::cout << "Hi I'm the function 2 after sleeping" << std::endl;
   }
}

int main1()
{
   std::thread t1(function1);
   std::thread t2(function2);

   t1.join();
   t2.join();
}
