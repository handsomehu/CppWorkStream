#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <iostream>
#include <list>
template<typename T>
class Vector {
public:
     explicit Vector(int s)
	 {
        if(s<0)
            throw std::length_error{"Vector Constructor: Nagetive value!"};
         elem = new T[s];
         for(int i =0;i!=s;++i)
            elem[i] = 0;
         sz =s;
	 }
     ~Vector()
    {
        delete[] elem;
    }
     Vector(const Vector& a): elem{new T[a.sz]}, sz{a.sz}               // copy constructor

	 {
     for (int i=0; i!=sz; ++i)    // copy elements
           elem[i] = a.elem[i];
	 }
     Vector& operator=(const Vector& a)    // copy assignment
     {
        T * p = new T[a.sz];
        for (int i = 0;i!=a.sz;++i)
            p[i]=a.elem[i];
        delete[] elem; // why not directly new elem[size]?why delete it? not understand
        elem = p;
        sz = a.sz;
        return *this;
     }

     Vector(Vector&& a) :elem{a.elem},sz{a.sz}//move constructor
     {
        a.elem = nullptr;
        a.sz = 0;
     }
     T& operator[](int i) //operator[]
     {
            if (i < 0 || size()<=i)
                throw std::out_of_range{"Vector::operator[]"};

            //another way to do it, only on debug mode
            assert(i< size());
            return elem[i];
     }

     int size() const
     {return sz;}
     T* begin(Vector<T>& x )
     {
        return x.size()?&x[0]:nullptr;
     }
     T* begin()
     {
        return size()?&elem[0]:nullptr;
     }
     T* end(Vector<T>& x)
     {
        return x.size()?&x[0]+x.size():nullptr;
     }
     T* end()
     {
        return size()?&elem[0]+size():nullptr;
     }
private:
     T* elem;      // elem points to an array of sz doubles
     int sz;
};
//C++20 feature, not supported by my compiler
/*
template<typename TT, int N>
struct Buffer
{
    using value_type = TT;
    constexpr int size() {return N;}
    TT[N];
};
*/
template<typename Sequence, typename Value>
Value sum(Sequence& s, Value v)
{
    for(auto x:s)
        v+= x;
    return v;
}

void use_sum123(Vector<int> vi);

class Vector1  //
{
public:
    Vector1(std::initializer_list<double> lst);
    ~Vector1();
    void push_back(double f);
private:
     double* elem;      // elem points to an array of sz doubles
     int sz;
};
void testfunc(std::vector<int> v,std::vector<int>& rv);

class Container
{
public:
    virtual double& operator[](int)=0;
    virtual int size() const = 0;
    virtual ~Container(){}

};
class Vector_container: public Container
{
public:
    Vector_container(int s);
    ~Vector_container();
    double& operator[](int i) override;
    int size() const override;
private:
    Vector<double> v;

};
void ggg();

class List_container:public Container
{
public:
    List_container();
    //List_container(std::initializer_list<double> il);
    List_container(std::initializer_list<double> il);
    ~List_container();
    double& operator[](int i) override;
    int size() const override;
private:
std::list<double> ld;
};

void bad_copy(Vector<double> v1);

Vector<double> test_move();


#endif // VECTOR_H_INCLUDED
