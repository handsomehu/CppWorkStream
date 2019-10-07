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
#endif // STDTEST_H_INCLUDED
