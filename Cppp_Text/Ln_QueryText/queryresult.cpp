#include "queryresult.h"

QueryResult::QueryResult(std::string s,
                         std::shared_ptr<std::set<TextQuery::line_no>> p,
                         std::shared_ptr<std::vector<std::string>> f)
    :sought(s),line(p),file(f)
{

}
std::ostream& print(std::ostream &os,const QueryResult &qr)
{
    os << qr.sought << "occurs:" << qr.line->size() << " times." << std::endl;
    for(auto ln:(*qr.line))
        os << "(" << ln+1 << ") " << *(qr.file->begin() + ln) << std::endl;

}
