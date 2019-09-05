#include <iostream>
#include "vector.cpp"

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
void fffa(Entry* pe)
{
    if(pe->t == num)
       int i = pe->v.i;
};
double read_and_sum(int s)
{
	Vector v(s);
	for (int i = 0; i != v.size();++i)
		std::cin >> v[i];
	double sum = 0;
	for (int i = 0; i != v.size();++i)
		sum+= v[i];
	return sum;

}
int main()
{
    std::cout << "Hello world!" << std::endl;
    std::cout << "Sum until 10 is :" << read_and_sum(10) << std::endl;
    return 0;
}
