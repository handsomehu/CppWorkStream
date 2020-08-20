#ifndef LZPERSON_H
#define LZPERSON_H
#include <iostream>
#include <vector>

struct lzperson
{
    std::string name;
    int age;
};
class lzpersons
{
public:
    lzpersons();
    readpersons();

private:
    std::vector<lzperson> psz;
};

std::ostream& operator<<(std::ostream& os, const lzpersons& p);
{
return os << "{\"" << e.name << "\", " << e.number << "}";
}
#endif // LZPERSON_H
