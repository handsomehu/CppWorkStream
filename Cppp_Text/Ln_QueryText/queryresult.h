#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include "textquery.h"
class QueryResult
{
friend std::ostream& print(std::ostream &,const QueryResult &);
public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f);
private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> line;
    std::shared_ptr<std::vector<std::string>> file;
};
std::ostream& print(std::ostream &,const QueryResult &);
#endif // QUERYRESULT_H
