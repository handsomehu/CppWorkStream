#include "strblob.h"

StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>())
{

}

StrBlob::StrBlob(std::initializer_list<std::string> il)
    :data(std::make_shared<std::vector<std::string>>(il))
{

}

StrBlob::size_type StrBlob::size() const{ return data->size(); }
bool StrBlob::empty() const { return data->empty(); }
void StrBlob::push_back(const std::string &t) {data->push_back(t);}
void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}
std::string & StrBlob::front()
{
    check(0,"out of range");
    return data->front();
}
std::string& StrBlob::back()
{
    check(0,"out of range");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0,"out of range");
    data->pop_back();
}
