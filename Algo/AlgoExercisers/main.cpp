#include <iostream>
#include <vector>

int binsort(std::vector<int>& sorted,int target)
{
    int low{0},high{0},mid{0},guess{0};
    high = sorted.size()-1;
    //std::cout << high << std::endl;
    mid = (low+high)/2;
    while(low <=high)
    {
        if (target == sorted[mid])
            return mid;
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
                std::cout << idx << std::endl;

            }
        }
        out.push_back(temp);
        data[idx] = 0;//urgly, I know, without pop, this is the way i come up with;


    }
    return out;


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
    return 0;
}
