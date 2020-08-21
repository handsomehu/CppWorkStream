#include "lzpersons.h"

lzpersons::lzpersons()
{

}

std::ostream& operator<<(std::ostream& os, const lzpersons& p)
{
    for(lzperson ps:p.psz)
    {
        os << ps.name << "    " << ps.age << std::endl;
    }
    return os;

}
lzperson lzpersons::split (const std::string &s, char delim)
{
    lzperson tp{};

    std::stringstream ss (s);
    std::string item;
    int cnt{0};

    std::getline(ss, item, delim);
    tp.name = item;
    std::getline(ss, item, delim);
    tp.age = stoi(item);

    return tp;
}
void lzpersons::addps(lzperson & newps)
{
    psz.push_back(newps);

}
std::istream& operator>>(std::istream& is, lzpersons& p)
{
    std::string inputstr;
    char delim = ',';
    while (std::getline(is, inputstr))
    {
        lzperson p1 = p.split(inputstr, delim);
        //is << p1.name << "    " << p1.age << std::endl;
        p.addps(p1);
    }
    return is;

}
