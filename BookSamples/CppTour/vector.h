#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <iostream>
#include <list>

class Vector {
public:
     Vector(int s);
     ~Vector();
     Vector(const Vector& a);               // copy constructor
     Vector& operator=(const Vector& a);    // copy assignment
     Vector(Vector&& a); //move constructor
     double& operator[](int i);
     int size() const;
private:
     double* elem;      // elem points to an array of sz doubles
     int sz;
};

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
    Vector v;

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

void bad_copy(Vector v1);

Vector test_move();
#endif // VECTOR_H_INCLUDED
