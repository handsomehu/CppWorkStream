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
};
void testreg()
{
    std::ifstream in("./zip.txt");
    if(!in)
        std::cerr << "no file" << std::endl;
    std::regex pat {R"(\w{2}\s*\d{5}(−\d{4})?)"};  // U.S. postal code pattern:
                                                    //XXddddd-dddd and variants
    int lineno = 0;
    for(std::string line;std::getline(in,line);)
    {
        ++lineno;
        std::cout << line;

        std::smatch matches;
        if(regex_search(line,matches,pat))
        {
            std::cout << lineno << ": " << matches[0] << '\n';
        }
    }
    std::string input = "aa as; asd ++e^asdf asdfg";
    std::regex pat1{R"(\s+(\w+))"};
    for (std::sregex_iterator p(input.begin(),input.end(),pat1); p!=std::sregex_iterator{}; ++p)
           std::cout << (*p)[1] << '\n';
}


