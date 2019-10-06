#include "./src/stdtest.h"

std::string compose(const std::string& name, const std::string& domain )
{
    std::string tempstr = "test +=: ";
    //std::string cppname = "Niels Stroustrup";
    tempstr += "looks good!";
    std::cout << tempstr << std::endl;
    std::string cppname = "Niels Stroustrup";
    tempstr = cppname.substr(6,10);
    std::cout << tempstr << std::endl;
    cppname.replace(0,5,"nicholas");
    cppname[0] = std::toupper(cppname[0]);
    std::cout << cppname << std::endl;
    return name + "@" + domain;
};
void testprint(const std::string& s)
{
    printf("For people who like printf: %s\n",s.c_str());
    std::cout << "For people who like streams: " << s << '\n';
    auto sss = "Cat"s;//a std::string
    auto p = "Dog";//a C-style string: a const char*
}

