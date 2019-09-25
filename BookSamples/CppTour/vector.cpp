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
Vector::Vector(const Vector &a): elem{new double[a.sz]}, sz{a.sz}
	{
     for (int i=0; i!=sz; ++i)    // copy elements
           elem[i] = a.elem[i];
	}
//move constructor
//still got a bit confuse about rvalue and reference of rvalue
//anyway it works.
Vector::Vector(Vector&& a):elem{a.elem},sz{a.sz}
{
    a.elem = nullptr;
    a.sz = 0;
}

Vector& Vector::operator=(const Vector& a)   // copy assignment
{
    double * p = new double[a.sz];
    for (int i = 0;i!=a.sz;++i)
        p[i]=a.elem[i];
    delete[] elem; // why not directly new elem[size]?why delete it? not understand
    elem = p;
    sz = a.sz;
    return *this;
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

void bad_copy(Vector v1)
{
    Vector v2 = v1; //copy v1's representation into v2
    v1[0] = 2;         // v2[0] is now also 2!
    v2[1] = 3;         // v1[1] is now also 3!
    //default copy constructure is very bad for resource handle
}

Vector test_move()
{
    Vector x(20);
    Vector y(30);
    Vector z(40);

    z = x; //copy x to z
    y = std::move(x); // move assignment, should not use x any more
    return z; //move z is ready to gone

}
