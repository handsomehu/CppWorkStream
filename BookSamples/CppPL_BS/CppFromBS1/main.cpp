#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <memory>
#include <cstddef>
#include <chrono>
#include "bsstring.h"
using namespace std;

constexpr int ftbl[] { 1, 2, 3, 5, 8, 13 };

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
void test_limit()
{
    cout << "size of long " << sizeof(1L) << '\n';
    cout << "size of long long " << sizeof(1LL) << '\n';
    cout << "largest float == " << std::numeric_limits<float>::max() << '\n';
    cout << "char is signed == " << std::numeric_limits<char>::is_signed << '\n';
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
void user123(const vector<int>& vx)
{
constexpr int bufmax = 1024;
alignas(int) int buffer[bufmax]; // uninitialized
const int max = min(vx.size(),bufmax/sizeof(int));
uninitialized_copy(vx.begin(),vx.begin()+max,buffer);
cout << buffer[0] << endl;
// ...
}
void testuse()
{
    vector<int> tv{8,1,2,3};
    user123(tv);

}
int testpf(char* str)
{
    if (str)
        return 0;
    else
        return -1;
}
void testpv(int* pi)
{
    void* pv;
    pv = pi;
    int ti =  0;
    //*pv ;
    //++pv;
    //cout << ti << endl;
    int* pi2 = static_cast<int*>(pv);
    cout << *pi2 << endl;

}
void testpointer()
{
    int i1{10};
    int* pi; //pointer to int
    pi = &i1;
    cout << *pi << endl;
    char** ppc;
    char c1{'d'};
    char* pc=&c1;
    ppc = &pc;
    cout << "address of pc:" << ppc << "value of pc" << *ppc << endl;
    cout << "value of char:" << **ppc << endl;
    int* ap[15];
    cout << ap[0] << endl;
    int (*fp)(char*) ;
    fp = testpf;
    char* tc= "Hello World";
    cout << "result" << fp(tc) << endl;
    testpv(pi);



}
void print_mij(int* m, int dim1, int dim2)
{
for (int i = 0; i!=dim1; i++)
    {
    for (int j = 0; j!=dim2; j++)
        cout << m[i*dim2+j] << '\t'; // obscure
    cout << '\n';
    }
}
 int isqrt_helper(int sq, int d, int a)
{
    int t1 = 0;
    t1 = (sq <= a ? isqrt_helper(sq+d,d+2,a) : d);
    cout << "helper" << t1 << endl;

    return t1;
}
 int isqrt(int x)
{
    int t2 = 0;
    t2 = (isqrt_helper(1,3,x)/2-1);
    cout << "isqrt:" << t2 << endl;
    return t2;
}

 void test_prio()
 {
    //std::cout << (6 << 2) << std::endl;
    //std::cout << (3 << 2) << std::endl;
    //return;
    int b = 2,c=3,d =1;
    int a = ((b + (c*d)) << 2) & 8;
    int x = b + c*d << 2 & 8;
    a = 1;
    b = a & 077 != 3;
    a == b || a == c && c < 5;

    std::cout << a << "," << x << std::endl;
 }


 constexpr int fib(int n)
 {
    return (n<sizeof(ftbl)/sizeof(*ftbl)) ? ftbl[n] : fib(n);
 }

void test_string()
{
    String s ("abcdefghij");
    cout << s << '\n';
    s += 'k';
    s += 'l';
    s += 'm';
    s += 'n';
    cout << s << '\n';
    String s2 { "Hell"};
    s2 += String{" and high water"};
    cout << s2 << '\n';
    String s3 { "qwerty"};
    s3 = s3;
    String s4 {"the quick bro wn fox jumped over the lazy dog"};
    s4 = s4;
    cout << s3 << " " << s4 << "\n";
    cout << s + String{". "} + s3 + String(". ") + String{"Horsefeathers\n"};
    String buf;
    while (cin>>buf && buf!=String{"quit"})
    cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
}
int main()
{
    locale loc("");
    cout << loc.name() << '\n';
    test_string();
    return 0;
    test_prio();
    cout << "start fib" << std::endl;
    cout << fib(7) << std::endl;
    return 0;
     //int s1 = isqrt(9); // s1 becomes 3
     int s2 = isqrt(4);
     cout << s2 << endl;
    cout << "Hello World!" << endl;
    //test_si();
    digits();
    test_limit();
    testuse();
    testpointer();
    return 0;
}
