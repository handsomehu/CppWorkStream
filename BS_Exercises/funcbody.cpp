#include "funcheader.h"
void nameage()
{
    std::string name{""};
    int age{0};
    std::cout << "please input a name:" << std::endl;
    std::cin >> name  ;
    std::cout << "please input age:" << std::endl;
    std::cin >> age  ;
    std::cout << "name:" << name << " age:" << age;

}
