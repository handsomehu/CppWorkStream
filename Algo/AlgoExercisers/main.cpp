#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "algofuncs.h"

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
std::list<int>::iterator select_sort_max(std::list<int> & sample)
{
    int idx{0},temp{0};
    std::list<int>::iterator maxit{sample.begin()};

    for(auto p = sample.begin();p!=sample.end();++p)
        if (*p>*maxit)
            maxit = p;
    return maxit;

}

int qs_part1(int samples[],int low, int high)
{
    int p_index{low},temp{0};
    int pivot = samples[low];
    for(int i = low+1;i<=high;++i)
    {
        if (samples[i]<=pivot)
        {
            temp = samples[p_index];

            samples[p_index]=samples[i];
            samples[i] = temp;
            ++p_index;
        }

    }
    return p_index;
}

int qs_part(int samples[],int low, int high)
{
    int pivot{samples[high]};
    int p_index = low;
    int temp{0};

    for( int i = low;i< high;++i)
    {
        //std::cout << std::to_string(i) << std::endl;
        if (samples[i]<=pivot)
        {
            temp = samples[p_index];
            samples[p_index] = samples[i];
            samples[i]=temp;
            ++p_index ;
        }

    }
    temp = samples[p_index];
    samples[p_index] = samples[high];
    samples[high] = temp;

    return p_index;
}
void quick_sort(int samples[],int low, int high)
{
    int idx{0};
    if (low < high)
    {   idx = qs_part1(samples,low, high);
        //return;
        quick_sort(samples,low,idx-1);
        quick_sort(samples,idx+1,high);
    }

}
void select_sort2(std::list<int>& sample)
{
    std::list<int> tgt{};
    std::list<int>::iterator temp{};
    int scnt = sample.size();
    for (auto idx = 0;idx != scnt;++idx)
    {
        temp = select_sort_max(sample);
        tgt.push_back(*temp);
        sample.erase(temp);
    }
    for(auto x:tgt)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

}
// remove duplicated from a sorted table
int rm_duplval(std::vector<int>& arr)
{
    int idx{1};
    if (arr.size() ==0)
        return 0;
    for (int i=1;i<arr.size();++i)
    {
        if(arr[i] != arr[idx-1])

            arr[idx++] =  arr[i]; }

    return idx;

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
    std::vector<int> tt{1,2,9,8,9,5,6,4};
    int idx = fcpeak(tt,0,tt.size());
    std::cout << "idx is : " << idx << std::endl;
    std::cout << int(1/2) << std::endl;
    std::vector<int> arr{1,1,2,2,2,2,3,6,6,6,7};
    std::cout << std::to_string(rm_duplval(arr));
    return 0;
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
    select_sort2(lt);
    std::cout << "factories of 5:" << fact_test(5) << std::endl;
    std::cout << "start fast sort:" << std::endl;
    constexpr int sz = 15;
    int fstest[sz]{8,19,1,5,2,3,34,21,50,48,66,38,77,55,88};
    //int* p1;
    quick_sort(fstest,0,14);
    std::vector<int> fsv{3,2,5,1} ;//{3,2,5,1,19,8};

    for(int iii=0;iii!=sz;++iii)
    {
        std::cout << fstest[iii] << " ";
    }
    std::cout << std::endl;
    return 0 ;

}
