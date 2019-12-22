//#include <iostream>
#include "basic_type.h"
#include "token_stream.h"
#include <sstream>

//using namespace std;
//std::istream is{std::cin};
Token_stream ts(std::cin);
std::map<std::string,double> table;
int no_of_errors;
int main(int argc, char* argv[])
{
    switch (argc) {
    case 1: // read from standard input
    break;
    case 2: // read from argument string
        ts.set_input(new std::istringstream{argv[1]});
    break;
    default:
    error("too many arguments");
    return 1;
    }
    table["pi"] = 3.1415926535897932385; // inser t predefined names
    table["e"] = 2.7182818284590452354;
    calculate();
    return no_of_errors;
}
