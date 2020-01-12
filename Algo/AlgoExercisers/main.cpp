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

int* fast_search(int* samples,int arrsize)
{
    int temp{0},baseval{0};
    int j{0},k{0};
    int* l;
    int* r;
    static int tm{0};
    std::cout << "times: " << ++tm << std::endl;
    if ( arrsize < 2 )
        return samples;
    else
    {
    //int fstest[5]{3,5,1,7,2};
        temp = 0;
        int l[arrsize]; // give size is 3, l[1], right[1]
                     // give size is 4, l[2], right[1]
        int r[arrsize];
        baseval = samples[temp];
        for(int i = 0+1;i!= arrsize;++i)
        {
            if (*(samples+i) <= baseval)
                l[j++] = samples[i];
            else if (*(samples+i) > baseval)
                r[k++] = samples[i];

        }
        std:: cout << "j:" << j << " k:" << k << std::endl;
        int* la = fast_search(l,j);
        int* ra = fast_search(r,k);

        if ((j + k +1 ) == arrsize)
        {
            for(int i1 = 0;i1!=j;++i1)
                *(samples+i1) = la[i1];
            *(samples+j) = baseval;
            for(int i2 = 0;i2!=k;++k)
                *(samples+j+i2+ 1)= ra[i2];
        }
        return samples;


    }
        //fast_search(samples+1,arrsize-1);
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
    std::cout << "start fast sort:" << std::endl;
    constexpr int sz = 6;
    int fstest[sz]{3,2,5,1,19,8};
    int* p1;
    p1 = fast_search(fstest,sz);
    for(int iii=0;iii!=sz;++iii)
    {    std::cout << *(p1+iii) << std::endl;

    }
    return 0;
}
