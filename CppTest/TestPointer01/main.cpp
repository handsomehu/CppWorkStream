#include <iostream>


int main()
{
    struct node
    {
        int a;
        int b;
        int c;

    };
    struct node s = {3,5,6};
    struct node *pt = &s;
    std::cout << pt << std::endl;
    std::cout << (int*)pt << std::endl;
    printf("%d", *((int*)pt+1));
    std::cout << std::endl;

    return 0;
}
