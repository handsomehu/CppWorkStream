#include "./vector.h"

Vector::Vector(int s)
	{
        if(s<0)
            throw std::length_error{"Vector Constructor: Nagetive value!"};
         elem = new double[s];
         for(int i =0;i!=s;++i)
            elem[i] = 0;
         sz =s;
	}
Vector::~Vector()
{
    delete[] elem;
}
double& Vector::operator[](int i)
	{
        if (i < 0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};

        //another way to do it, only on debug mode
        assert(i< size());
        return elem[i];
    }
int Vector::size() const
	{return sz;}


void testfunc(std::vector<int> v,std::vector<int>& rv)
{
    v[1]= 99;
    rv[2] = 66;
}

Vector1::Vector1(std::initializer_list<double> lst):
    elem{new double[lst.size()]},sz{static_cast<int>(lst.size())}
    {
        std::copy(lst.begin(),lst.end(),elem);
    }
Vector1::~Vector1()
{
    delete[] elem;
}

void Vector1::push_back(double f)
{
    //push back: how to increase the array size without copy data?
    //push back

    //increase size
    sz += 1;
}

Vector_container::Vector_container(int s):v(s)
{}
Vector_container::~Vector_container(){}
double&  Vector_container::operator[](int i)
{
    return v[i];
}

int  Vector_container::size() const
{
    return v.size();
}

void use(Container& c)
{

    const int sc = c.size();
    for (int i = 0;i!= sc;++i)
        std::cout << c[i] << std::endl;
}
void ggg()
{
    Vector_container vc(10);
    use(vc);
}
