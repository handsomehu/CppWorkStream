#ifndef HASPTR_H
#define HASPTR_H
#include <string>

class HasPtr
{
friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string());
    HasPtr(const HasPtr &hp);
    HasPtr& operator=(const HasPtr &rhs);
    ~HasPtr(){delete ps;}

private:
    std::string *ps;
    int i;
};


class HasPtrRef
{
public:
    HasPtrRef(const std::string &s = std::string());
    HasPtrRef(const HasPtrRef &hp);
    HasPtrRef& operator=(const HasPtrRef &rhs);
    ~HasPtrRef()
    {
        if (--*use == 0)
        {
            delete use;
            delete ps;
        }
    }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps); // swap the pointers, not the string data
    swap(lhs.i, rhs.i); // swap the int members
}
#endif // HASPTR_H
