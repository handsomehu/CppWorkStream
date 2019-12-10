#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
int test_si()
{
string from, to;
cin >> from >> to; // get source and target file names
ifstream is {from}; // input stream for file "from"
istream_iterator<string> ii {is}; // input iterator for stream
istream_iterator<string> eos {}; // input sentinel
ofstream os{to}; // output stream for file "to"
ostream_iterator<string> oo {os,"\n"}; // output iterator for stream
vector<string> b {ii,eos}; // b is a vector initialized from input [ii:eos)
sort(b.begin(),b.end()); // sor t the buffer
unique_copy(b.begin(),b.end(),oo); // copy buffer to output, discard replicated values
return !is.eof() || !os; // return error state (§2.2.1, §38.3)
}
void digits()
{
    for(int i = 1;i!=10;++i)
        cout << static_cast<char>('0'+i);
    char c = 255;
    int ci = c;
    cout << ci << std::endl;
}
void g111(char c, signed char sc, unsigned char uc)
{
    c = 255; // implementation-defined if plain chars are signed and have 8 bits
    c = sc; // OK
    c = uc; // implementation-defined if plain chars are signed and if uc’s value is too large
    sc = uc; // implementation defined if uc’s value is too large
    uc = sc; // OK: conversion to unsigned
    sc = c; // implementation-defined if plain chars are unsigned and if c’s value is too large
    uc = c; // OK: conversion to unsigned

}
int main()
{
    cout << "Hello World!" << endl;
    //test_si();
    digits();
    return 0;
}
