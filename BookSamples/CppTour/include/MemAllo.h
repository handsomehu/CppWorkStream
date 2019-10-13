#ifndef MEMALLO_H
#define MEMALLO_H
#include <vector>
#include <list>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <functional>
class theShape
{
public:
    void Draw(){};
};
void draw_all1(const std::vector<theShape>& v);
void draw_all2(const std::vector<theShape>& v);
void draw_all3(const std::vector<theShape>& v);
struct fakeEvent
{
    std::vector<int> data = std::vector<int>(512);

};
std::mutex m;
std::list<std::shared_ptr<fakeEvent>> q;
std::condition_variable cv;
//std::lock_guard lg;
void prodecer();
//C++17 fix:
/*
pmr::synchronized_pool_resource pool; // make a pool
struct Event {
vector<int> data = vector<int>{512,&pool}; // let Events use the pool
};
list<shared_ptr<Event>> q {&pool}; // let q use the pool
void producer()
{
for (int n = 0; n!=LOTS; ++n)
    {
    scoped_lock lk {m}; // m is a mutex (§15.5)
    q.push_back(allocate_shared<Event,pmr::polymorphic_allocator<Event>>{&pool});
    cv.notify_one();
    }
}

*/

class MemAllo
{
    public:
        MemAllo();
        virtual ~MemAllo();

    protected:

    private:
};

#endif // MEMALLO_H
