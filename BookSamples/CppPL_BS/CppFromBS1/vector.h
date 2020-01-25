#ifndef VECTOR_H
#define VECTOR_H
#include <memory>
#include <iterator>

template<class For, class T>
void uninitialized_fill(For beg, For end, const T& x);

template<class T, class A = std::allocator<T>>
class vector
{
public:
    using size_type = unsigned int;
    explicit vector(size_type n, const T& val = T(), const A& = A());
    vector(const vector& a); // copy constr uctor
    vector& operator=(const vector& a); // copy assignment
    vector(vector&& a); // move constr uctor
    vector& operator=(vector&& a); // move assignment
    ~vector();
    size_type size() const { return space-elem; }
    size_type capacity() const { return last-elem; }
    void reserve(size_type n);
    void resize(size_type n, const T& = {}); // increase size to n
    void push_back(const T&); // add
private:
    T* elem; // star t of allocation
    T* space; // end of element sequence, star t of space allocated for possible expansion
    T* last; // end of allocated space
    A alloc; // allocator
};

#endif // VECTOR_H
