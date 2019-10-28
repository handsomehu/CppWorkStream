#ifndef STRBLOB_H
#define STRBLOB_H
#include <vector>
#include <string>
#include <memory>
#include <exception>
class StrBlob
{

public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const;
    bool empty() const;
    void push_back(const std::string &s);
    void pop_back();
    std::string & front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

#endif // STRBLOB_H
