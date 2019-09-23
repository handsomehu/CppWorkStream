#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>
#include <assert.h>
#include <vector>

class Vector {
public:
     Vector(int s);
     ~Vector();
     double& operator[](int i);
     int size();
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

#endif // VECTOR_H_INCLUDED
