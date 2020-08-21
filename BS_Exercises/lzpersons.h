#ifndef LZPERSON_H
#define LZPERSON_H
#include <iostream>
#include <sstream>
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
    std::ostream& operator<<(std::ostream& os);
    std::istream& operator>>(std::istream& is);
    lzperson split (const std::string &s, char delim);
    void addps(lzperson & newps);
private:
    std::vector<lzperson> psz;


friend std::ostream& operator<<(std::ostream& os, const lzpersons& p);
friend std::istream& operator>>(std::istream& is, lzpersons& p);
};
//std::ostream& operator<<(std::ostream& os, const lzpersons& p);

#endif // LZPERSON_H
