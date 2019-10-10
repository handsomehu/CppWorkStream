#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <iostream>
#include <list>
#include <unordered_set>
#include <algorithm>
template<typename T>
class Vector {
public:
     explicit Vector(int s)
	 {
        if(s<0)
            throw std::length_error{"Vector Constructor: Nagetive value!"};
         elem = new T[s];
         //for(int i =0;i!=s;++i)
         //   elem[i] = 0;
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
     int capacity();
     void reserve(int newsz);
     void push_back(const T& t)  //copy t to the vector
     {
        if (capacity()< size()+1)
            reserve(size() ==0?8:2*size());
        new(space) T{t};// initialize *space to t
                        //this is placement new, not totally understand
                        //placement new seperate allocate memory and constructor data within it
                        //it constructor data at pre-allocated memory.
        space++;
     }
     void push_back(T&& t);       //move t to the vector
     T* begin() const
     {
        return size()?&elem[0]:nullptr;
     }
     T* end(Vector<T>& x)
     {
        return x.size()?&x[0]+x.size():nullptr;
     }
     T* end() const
     {
        return size()?&elem[0]+size():nullptr;
     }
private:
     T* elem;      // elem points to an array of sz doubles
     T* space;
     T* last;
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
// Function Templates
// A function template can be a member function(of a class),
//but not a virtual member.
template<typename Sequence, typename Value>
Value sum(const Sequence& s, Value v)
{
    for(auto x:s)
        v+= x;
    return v;
}

//Functor or Function objects example
template<typename T>
class Less_Than
{
const T val;

public:
    Less_Than(const T& v): val{v}{}
    bool operator()(const T& x) const
    {
        return x < val;
    }
};
void use_sum123(Vector<int>& vi);

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

struct Record
{
    std::string name;
    int product_code;
    bool operator<(const Record& rhs)   // less than
    {
         return this->name < rhs.name;       // order Entries by their names
    }
};
struct Rhash
{
    std::size_t operator()(const Record& r) const
    {
        return std::hash<std::string>()(r.name) ^ std::hash<int>()(r.product_code);
    }

};

bool has_c(const std::string& s, char c);
std::vector<std::string::iterator> find_all(std::string& s, char c);
//
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

template<typename C,typename P>
int count(const C& c, P pred)
//requires Sequence<C> && Callable<P,Value_type<P>>
//Function objects used to specify the meaning of key operations of a general algorithm
//(such as Less_than for count()) are often referred to as policy objects.
{
    int cnt = 0;
    for(const auto &x:c)
        if(pred(x))
            ++cnt;
    return cnt;

}
void test_lambda();
#endif // VECTOR_H_INCLUDED
