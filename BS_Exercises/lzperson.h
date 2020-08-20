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
    std::vector<lzperson>& readpersons() const;
    std::ostream& operator<<(std::ostream& os);
    std::ostream& operator>>(std::ostream& os);
private:
    std::vector<lzperson> psz;
};

//std::ostream& operator<<(std::ostream& os, const lzpersons& p);

#endif // LZPERSON_H
