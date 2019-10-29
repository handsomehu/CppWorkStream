#include "textquery.h"
#include "queryresult.h"
TextQuery::TextQuery(std::ifstream &is):file(new std::vector<std::string>)
{
    std::string text;
    while(std::getline(is,text))
    {
       file->push_back(text);
       int n = file->size()-1;
       std::istringstream line(text);
       std::string word;

       while(line >>word)
       {
           auto &line = wm[word];
           if (!line)
               line.reset(new std::set<line_no>);
           line->insert(n);
       }


    }
}

QueryResult TextQuery::query(const std::string & sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
     auto loc = wm.find(sought);
     if (loc != wm.end())
         return QueryResult(sought,loc->second,file);
     else
         return QueryResult(sought,nodata,file);
}
