#include "algofuncs.h"

int fcpeak(std::vector<int> nums, int low, int high)
{
    int idx = low + (high-low)/2;

    if (idx > low and idx < high)
    {

        if (nums[idx] < nums[idx-1])
            return   fcpeak(nums,low,idx-1);

        else if (nums[idx] < nums[idx+1])
            return fcpeak(nums,idx+1,high);
        else
            return idx;
    }
    else if (idx  == low)
    {
        if (nums[idx] > nums[idx+1])
            return idx;
        else
            return fcpeak(nums,idx+1,high);

    }
    else if (idx == high)
        if (nums[idx-1] < nums[idx])
            return idx;
        else
            return fcpeak(nums,low, idx-1);
    else
        return idx;

}
