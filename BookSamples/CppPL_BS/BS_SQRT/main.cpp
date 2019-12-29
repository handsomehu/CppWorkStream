#include <iostream>
// This is how Bjarne Handle Int Square root
using namespace std;
constexpr int isqrt_helper(int sq, int d, int a)
{
return sq <= a ? isqrt_helper(sq+d,d+2,a) : d;
}
constexpr int isqrt(int x)
{
return isqrt_helper(1,3,x)/2- 1;
}
int main()
{
    int sqr{0};
    cin >> sqr;
    cout << isqrt(sqr) << endl;
    return 0;
}
