#include "MemAllo.h"


void draw_all1(const std::vector<theShape*>& v)
{
    for_each(v.begin(),v.end(),[](theShape* p){p->Draw();});
}
void draw_all2(const std::vector<theShape*>& v)
{
    for_each(v.begin(),v.end(),std::mem_fn(&theShape::Draw));
}
void draw_all3(const std::vector<theShape*>& v)
{
    std::function<void(theShape*)> fct3 = [](theShape* p){p->Draw();};
    for_each(v.begin(),v.end(),fct3);
}



void producer() // this will cause lots of fragmatation
//to fix this c++17 offer pool allocator via pmr::synchronized_pool_resource
//I do not have C++17, boost has library, does Qt have it?
{
    for (int n = 0; n!=100000; ++n)
    {
        std::lock_guard<std::mutex> lk {m}; // m is a mutex (§15.5)
        q.push_back(std::make_shared<fakeEvent>());
        cv.notify_one();
    }
}
MemAllo::MemAllo()
{
    //ctor
}

MemAllo::~MemAllo()
{
    //dtor
}
