#ifndef STDTEST_H_INCLUDED
#define STDTEST_H_INCLUDED
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
using namespace std::literals::string_literals;

std::string compose(const std::string& name, const std::string& domain );
void testprint(const std::string& s);

//std::string cat(std::string_view sv1, std::stringview sv2);
void testreg();
std::vector<int> read_ints(std::istream& is);
struct namecard
{
    std::string name;
    int number;
};
std::ostream& operator<<(std::ostream& os, const namecard& e);
std::istream& operator>>(std::istream& is, const namecard& e);
void testio();
#endif // STDTEST_H_INCLUDED
