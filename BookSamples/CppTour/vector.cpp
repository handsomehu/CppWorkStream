#include "./vector.h"
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
};




List_container::List_container(){};
//List_container::List_container(std::initializer_list il) : ld{il} {} //what the f*k?
List_container::List_container(std::initializer_list<double> il) :ld{il} {}
List_container::~List_container(){};
double& List_container::operator[](int i)
{
    for(auto& x:ld)
    {

        if (i==0)
            return x;
        --i;
    }
    throw std::out_of_range{"List container!"};
};

int List_container::size() const
{
    return ld.size();
};
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
    List_container lc={12,20.0,11.4};
    use(lc);
}

void bad_copy(Vector<double> v1)
{
    Vector<double> v2 = v1; //copy v1's representation into v2
    v1[0] = 2;         // v2[0] is now also 2!
    v2[1] = 3;         // v1[1] is now also 3!
    //default copy constructure is very bad for resource handle
}

Vector<double> test_move()
{
    Vector<double> x(20);
    Vector<double> y(30);
    Vector<double> z(40);

    z = x; //copy x to z
    y = std::move(x); // move assignment, should not use x any more
    return z; //move z is ready to gone

}
void use_sum123(Vector<int> vi)
{
    int ri = sum(vi,0);
    std::cout << ri << std::endl;
}
