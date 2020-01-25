#include "vector.h"
template<class For, class T>
void uninitialized_fill(For beg, For end, const T& x)
{
    For p;
    try
    {
        for (p=beg; p!=end; ++p)
            ::new(static_cast<void*>(&*p)) T(x); // construct copy of x in *p (§11.2.4)
    }
    catch (...)
    {
        for (For q = beg; q!=p; ++q)
        (&*q)->~T(); //destroy element (§11.2.4)
        throw; // rethrow (§13.5.2.1)
    }
}
template<class T, class A>
vector<T,A>::vector(size_type n, const T& val, const A& a) // warning: naive implementation
:alloc{a} //copy the allocator
{
    elem = alloc.allocate(n); // get memory for elements
    try {
    uninitialized_fill(elem,elem+n,val); // copy elements
    space = last = elem+n;
    }
    catch (...) {
    alloc.deallocate(elem,n); // free memory
    throw; // rethrow

}
