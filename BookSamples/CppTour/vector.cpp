#include "./vector.h"

Vector::Vector(int s)
	{
        if(s<0)
            throw std::length_error{"Vector Constructor: Nagetive value!"};
         elem = new double[s];
         sz =s;
	}
double& Vector::operator[](int i)
	{
        if (i < 0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};

        //another way to do it, only on debug mode
        assert(i< size());
        return elem[i];
    }
int Vector::size()
	{return sz;}


void testfunc(std::vector<int> v,std::vector<int>& rv)
{
    v[1]= 99;
    rv[2] = 66;
}
