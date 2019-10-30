#include "hasptr.h"

HasPtr::HasPtr(const std::string &s)
    :ps(new std::string(s)),i(0){};
HasPtr::HasPtr(const HasPtr &hp):ps(new std::string(*hp.ps)),i(hp.i)
{};
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newps = new std::string(*rhs.ps);
    delete ps;
    ps = newps;
    i = rhs.i;
    return *this;
}

HasPtrRef::HasPtrRef(const std::string &s)
    :ps(new std::string(s)),i(0),use(new std::size_t(1)){};

HasPtrRef::HasPtrRef(const HasPtrRef &hp):ps(hp.ps),i(hp.i),use(hp.use)
{
    ++*use;
}

HasPtrRef& HasPtrRef::operator=(const HasPtrRef &rhs)
{
    ++*rhs.use; // increment the use count of the right-hand operand
    if (--*use == 0)
    { // then decrement this object's counter
        delete ps; // if no other users
        delete use; // free this object's allocated members
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
