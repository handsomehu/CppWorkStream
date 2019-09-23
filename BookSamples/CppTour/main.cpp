#include <iostream>
#include <istream>
#include "./vector.h"
#include "udclass.cpp"

class Node {};
enum Type { ptr, num };
union Value {
     Node* p;
     int i;
};
struct Entry{
     char* name;
     Type t;
     Value v;  // use v.p if t==ptr; use v.i if t==num
};
struct Entry2
{
    char* name;
    //variant is c++17, not c++14
    //std::variant<Node*,int> v;
};
void fffa(Entry* pe)
{
    if(pe->t == num)
       int i = pe->v.i;
};

void fte(Vector& v)
{
    try
    {
        v[v.size()]= 7;
    }
    catch (std::out_of_range & err)
    {
        std::cerr << err.what() << "\n";
    }
}
double read_and_sum(int s)
{
	Vector v(s);
	for (int i = 0; i != v.size();++i)
		std::cin >> v[i];
	double sum = 0;
	for (int i = 0; i != v.size();++i)
		sum+= v[i];
    //Vector& r=v;
    fte(v);
	return sum;

}

int sum_v(const std::vector<int>& v)
{
    int sum = 0;
    for(int single:v)
        sum+= single;
    return sum;
}
enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };
Traffic_light& operator++(Traffic_light& t)
{
switch(t)
    {
    case Traffic_light::green: return t = Traffic_light::yellow;
    case Traffic_light::yellow: return t = Traffic_light::red;
    case Traffic_light::red: return t = Traffic_light::green;
    }
}


int& bad()
{
int x = 10;
return x;
}

struct Entry123 //Le'ts pretend Matrix123 is a matrix.
{
std::string name;
int value;
};
Entry123 read_entry123(std::istream& is)
{
    std::string s;
    int i;
    is >> s >> i ;
    return {s,i};
};

/*
map<string,int> m;
// ... fill m ...
for (const auto [key,value] : m)
      cout << "{" << key "," << value << "}\n";
void incr(map<string,int>& m)     // increment the value of each element of m
{
     for (auto& [key,value] : m)
           ++value;
}
read and write map
*/
    bool operator==(complex a, complex b) // equal
    {
    return a.real()==b.real() && a.imag()==b.imag();
    }
    bool operator!=(complex a, complex b) // not equal
    {
    return !(a==b);
    }
    complex sqrt(complex);
    complex operator+(complex a, complex b) { return a+=b; }
    complex operator-(complex a, complex b) { return a-=b; }
    complex operator-(complex a) { return {-a.real(), -a.imag()}; }
    // unary minus
    //complex operator*(complex a, complex b) { return a*=b; }
    //complex operator/(complex a, complex b) { return a/=b; }


void testcomplex()
{
    complex z = {1,0};
    const complex cz {1,3};
    z = cz;
    const complex cy(2,4);
    //cz = z;
    double x = z.real();
    bool eq = (z == cz);
    std::cout << "complex"  << x << std::endl;
    std::cout << "complex equal:" << eq << std::endl;
}

int main()
{
    std::cout << "Hello world!" << std::endl;
    std::cout << "Sum until 3 is :" << read_and_sum(3) << std::endl;


    Color col = Color::green;
    Traffic_light light = Traffic_light::red;
    ++light;
    std::cout << (int)light << std::endl;
    static_assert(4<=sizeof(int),"Int size does not match");

    std::vector<int> v1 = {1,2,3,5,8,13,21};
    static int sv = sum_v(v1);
    std::cout << sv << std::endl;
    testfunc(v1,v1);
    std::cout << v1[1] << "\t" << v1[2] << std::endl;

    //int rx = bad(); //complier did not consider this as error.
                    // B.St book said most complier will find this problem.
    //std::cout << rx << std::endl;
    auto e = read_entry123(std::cin);

    std::cout << e.name << e.value << std::endl;
    //auto [n,v] = read_entry123(std::cin); //not working in c++14 yet.
    //std::cout << n << v << std::endl;
    testcomplex();
    return 0;
};
