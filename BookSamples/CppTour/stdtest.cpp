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

std::ostream& operator<<(std::ostream& os, const namecard& e)
{
 return os << "{\"" << e.name << "\", " << e.number << "}";
}
std::istream& operator>>(std::istream& is, namecard& e)
{
    char c, c2;
    if (is >> c && c == '{' && is >>c2 && c2 == '"')
    {
        std::string name;
        while(is.get(c) && c!= '"')
            name+= c;
        if(is>>c && c== ',')
        {
            int number = 0;
            if(is>>number>>c &&c=='}')
                {e = {name,number};
                return is;}
        }
    }
    is.setstate(std::ios_base::failbit);
    return is;

}
std::vector<int> read_ints(std::istream& is,const std::string& terminator)
{
    std::vector<int> res;
    for(int i; is >> i; )

        res.push_back(i);
    if (is.eof())
        return res;
    if (is.fail())
        {
            is.clear(); // reset the state to good()
            is.unget(); // put the non-digit back into the stream
            std::string s;
            if (std::cin>>s && s==terminator)
                return res;
            std::cin.setstate(std::ios_base::failbit); // add fail() to cin's state
        }
        return res;
}
void testio()
{
    //std::istream tempis = std::cin;//could not copy;
    std::vector<int> vi = read_ints(std::cin,"stop");
    std::cout << "test io:" << vi.size() << std::endl;
    namecard nc{"Leon",123456789};
    std::cout << nc;
    std::cin>>nc;
    std::cout << "read in:" << nc.name << nc.number << std::endl;


}



