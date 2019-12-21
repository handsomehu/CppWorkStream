#ifndef BASIC_TYPE_H
#define BASIC_TYPE_H
#include <iostream>
enum class Kind : char
{
    name,number,end,plus='+',minus='-',mul='*',div='/',print=';',assign='=',lp='(',rp=')'
};
struct Token
{
    Kind kind;
    std::string string_value;
    double number_value;
};

#endif // BASIC_TYPE_H
