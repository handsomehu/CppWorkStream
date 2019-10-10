#include <iostream>
#include <istream>
#include "./vector.h"
#include <algorithm>
#include "udclass.cpp"
#include "./src/stdtest.h"
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

void fte(Vector<double>& v)
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
	Vector<double> v(s);
	std::cout << s << std::endl;
	for (int i = 0; i != v.size();++i)
		std::cin >> v[i];
	double sum = 0;
	for (int i = 0; i != v.size();++i)
		sum+= v[i];
    //Vector& r=v;
    fte(v);
	return sum;

}
void test_functor()
{
    Less_Than<int> t{5};
    std::cout<< "is 8 less than 5:" << t(8) << std::endl;
    Vector<int> v(5);
    v[0] = 3;
    v[1] = 4;
    v[2] = 5;
    v[3] = 6;
    v[4] = 7;
    int rv = count(v,t);
    std::cout << "number of less than 5:" << rv << std::endl;
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

void test_stdtest()
{
    auto dm = compose("handsomehu","github.com");
    std::cout << dm << std::endl;
    testprint(dm);
    testreg();
    std::cout << "before io push back run."<< std::endl;
    testio();

}
//extern void ggg();

void test_vi123()
{
     std::string m {"Mary had a little lamb"};
     for (auto p : find_all(m,'a'))
           if (*p!='a')
                 std::cerr << "a bug!\n";
}

void test_streamiterator()
{
    std::ostream_iterator<std::string> oo{std::cout};
    *oo = "Hello";
    ++oo;
    *oo = " World!\n";
    std::string from;
    std::string to;
    std::cin >> from >> to;
    std::ifstream is{from};
    std::istream_iterator<std::string> ii{is};
    std::istream_iterator<std::string> eof{};
    std::ofstream os{to};
    std::ostream_iterator<std::string> ooo{os,"\n"};
    std::vector<std::string> b{ii,eof};
    std::sort(b.begin(),b.end());
    std::unique_copy(b.begin(),b.end(),ooo);
    int rst = (!is.eof() || !os);
    std::cout << rst << std::endl;




}
void f1231(std::map<std::string,int>& m)
{
auto p = std::find_if(m.begin(),m.end(),Greater_Than{42});//Greater_Than is a functor;
}
int main()
{
    test_streamiterator();
    test_stdtest();
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
    std::cout << "test cb";
    ggg();
    Vector<double> ddd = test_move();
    Vector<int> v111(3);
    v111[0] = 1;
    v111[1] = 2;
    use_sum123(v111);
    test_functor();
    test_lambda();
    std::unordered_set<Record,Rhash> my_set;
    Record r1={"Leon",123};
    Record r2={"Zhao",456};
    bool abc = (r1 < r2);
    std::cout << "compare Record:" << abc << std::endl;
    test_vi123();
    return 0;
};
