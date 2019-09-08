#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>
#include <assert.h>
#include <vector>

class Vector {
public:
     Vector(int s);
     double& operator[](int i);
     int size();
private:
     double* elem;      // elem points to an array of sz doubles
     int sz;
};
void testfunc(std::vector<int> v,std::vector<int>& rv);

#endif // VECTOR_H_INCLUDED
