#include <iostream>
#include <vector>
#include <list>
#include <iterator>
//some example from book grokking algorithms
int binsort(std::vector<int>& sorted,int target)
{
    int cnt{0};
    int low{0},high{0},mid{0},guess{0};
    high = sorted.size()-1;
    //std::cout << high << std::endl;
    mid = (low+high)/2;
    while(low <=high)
    {
        if (target == sorted[mid])
        {
            std::cout << "step used:" <<cnt << std::endl;
            return mid;
        }
        else if (target < sorted[mid])
        {
            high = mid-1;
            mid = (low+high)/2;
        }
        else
        {
            low = mid+1;
            mid = (low+high)/2;
        }
        cnt+=1;


    }
    return 0;


}
std::vector<int> selectsort1(std::vector<int>& data)
{
    int temp{0},idx{0};
    std::vector<int> out{};

    for(int i = 0;i!=data.size();++i)
    {
        temp = 0;
        for (int j = 0;j!=data.size();++j)
        {if (data[j] > temp)
            {
                temp = data[j];
                idx = j;
                //std::cout << idx << std::endl;

            }
        }
        out.push_back(temp);
        data[idx] = 0;//urgly, I know, without pop, this is the way i come up with;


    }
    return out;


}
std::list<int>::iterator select_search_max(std::list<int> & sample)
{
    int idx{0},temp{0};
    std::list<int>::iterator maxit{sample.begin()};

    for(auto p = sample.begin();p!=sample.end();++p)
        if (*p>*maxit)
            maxit = p;
    return maxit;

}
void select_search2(std::list<int>& sample)
{
    std::list<int> tgt{};
    std::list<int>::iterator temp{};
    int scnt = sample.size();
    for (auto idx = 0;idx != scnt;++idx)
    {
        temp = select_search_max(sample);
        tgt.push_back(*temp);
        sample.erase(temp);
    }
    for(auto x:tgt)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

}


int fact_test(int val)
{
    if (val == 1)
        return val;
    else
        return val*fact_test(val-1);
}
int main()
{
    std::cout << "Hello World!" << std::endl;
    int tofind =0;
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10,24,34,36,40,50,56};
    while(std::cin>>tofind)
        std::cout<< binsort(v1,tofind) << std::endl;
    std::vector<int> st = selectsort1(v1);
    for(auto x:st)
        std::cout << x << " ";
    std::cout << std::endl;
    std::list<int> lt{1,2,3,4,5,6,7,8,9,10,24,34,36,40,50,56};
    select_search2(lt);
    std::cout << "factories of 5:" << fact_test(5) << std::endl;
    return 0;
}
