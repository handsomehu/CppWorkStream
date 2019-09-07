#include <iostream>
#include "./vector.h"

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



int main()
{
    std::cout << "Hello world!" << std::endl;
    std::cout << "Sum until 3 is :" << read_and_sum(3) << std::endl;


    Color col = Color::green;
    Traffic_light light = Traffic_light::red;
    ++light;
    std::cout << (int)light << std::endl;

    return 0;
}
