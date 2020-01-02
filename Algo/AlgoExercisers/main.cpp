#include <iostream>
#include <vector>

int fastsort(std::vector<int>& sorted,int target)
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

int main()
{
    std::cout << "Hello World!" << std::endl;
    int tofind =0;
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10,24,34,36,40,50,56};
    while(std::cin>>tofind)
        std::cout<< fastsort(v1,tofind) << std::endl;
    return 0;
}
