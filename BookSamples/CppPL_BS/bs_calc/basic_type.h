#ifndef BASIC_TYPE_H
#define BASIC_TYPE_H
#include <iostream>
#include <map>
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
double prim(bool get);
double term(bool get);
double expr(bool get);
double error(const std::string& s);
void calculate();
#endif // BASIC_TYPE_H
