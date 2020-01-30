#ifndef BSSTRING_H
#define BSSTRING_H
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <memory>
class String {
public:
    String(); //default constructor : x{""}
    explicit String(const char*p); //constructor from C-style string: x{"Euler"}
    String(const String&); // copy constr uctor
    String& operator=(const String& x); // copy assignment
    String& operator=(const char* cp);
    String(String&& x); // move constr uctor
    String& operator=(String&& x); // move assignment
    ~String() { if (short_max<sz) delete[] ptr; }; // destructor
    char& operator[](int n) { return ptr[n]; } // unchecked element access
    char operator[](int n) const { return ptr[n]; }
    char& at(int n) { check(n); return ptr[n]; } // range-checked element access
    char at(int n) const { check(n); return ptr[n]; }
    String& operator+=(char c); // add c at end
    const char* c_str() { return ptr; } // C-style string access
    const char* c_str() const { return ptr; }
    int size() const { return sz; } // number of elements
    int capacity() const // elements plus available space
    { return (sz<=short_max) ? short_max : sz+space; }

private:
    static const int short_max = 15;
    std::size_t sz; // number of characters
    char* ptr;
    union
    {
        int space; // unused allocated space
        char ch[short_max+1]; // leave space for terminating 0
    };
    void check(int n) const // range check
    {
    if (n<0 || sz<=n)
    throw std::out_of_range("String::at()");
    }

    // ancillar y member functions:
    void copy_from(const String& x);
    void move_from(String& x);
};
char* expand(const char* ptr, int n); // expand into free store
std::ostream& operator<<(std::ostream& os, const String& s);
std::istream& operator>>(std::istream& is, String& s);
bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);
char* begin(String& x);
char* end(String& x);
const char* begin(const String& x);
const char* end(const String& x);
String& operator+=(String& a, const String& b);
String operator+(const String& a, const String& b) ;
String operator"" _s(const char* p, size_t);

#endif // BSSTRING_H
