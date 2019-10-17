#include <iostream>
#include <vector>
#include "Sales_item.h"
#include "Sales_data.h"
#include <cctype>
#include <cstring>


void test_cstr()
{
    char ca[]={'C', '+', '+'};
    std::cout << "test strlen" ;
    std::cout << strlen(ca) << std::endl;//every run has diferent value, strange which is wrong
}
void test_ptr1()
{
    const int ci1{10};
    double obj = 3.14, *dp = &obj;
    void *vp = dp;
    int i = 2;
    int *p1 = &i;
    *p1 = *p1 * *p1;
    std::cout << *p1 << std::endl;
    int* p11, p12; // p1 is a pointer to int; p2 is an int
    // better way to do this is int *p11, p12;
    p11 = &i;
    p12 = 10;
    std::cout << "p11:" << *p11 << "p12:" <<p12 << std::endl;

    int *ptri = &i;
    int **pptri = &ptri;
    std::cout << "pptri" << *pptri << "*pptri" << **pptri << std::endl;

};
void test_const()
{
    // decltype of an expression can be a reference type
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b; // ok: addition yields an int; b is an (uninitialized) int
    decltype(*p) c= i; // *p , which * means de-reference, thus (*p) indicator it is a reference
};
void test_ptr2()
{
    int i = 42;
    int *p ;
    int *&r =p; // r is a pointer, which refece to p
    //int &rr = p; error, reference to int could not bind to pointer
    r = &i;
    *r = 0;
    std::cout << *r << std::endl;
    //int* ip, &rr = ip; //error could not bind ref to point
};
void test_vector()
{
    //const char a4[6] = "Daniel";// error
    std::vector<int> v1{42,65, 95, 100, 39, 67 ,95 ,76, 88 ,76 ,83 ,92, 76 ,93};
    std::vector<int> g(11,0);
    int gn = 0;
    for(const int x:v1 )
    {
        //++scores[grade/10]; //Author code, much better and simpler
        gn = x/10;
        if (x>100)
            std::cout << "bad number" << std::endl;
        g[gn]++;
    }
    for(const auto y:g)
        std::cout << y << " ";

}
void test_whilecin()
{
    std::string s;
    //while(std::cin >> s)
    //    std::cout << s;
    std::string ts{"some string!"};

    for(std::size_t idx =0;idx != ts.size()&&!isspace(ts[idx]);++idx)
            ts[idx] = toupper(ts[idx]);
    std::cout << "firsts words upper" << ts << std::endl;
    if (!ts.empty())
    {
        std::cout << ts[0] << std::endl;
        ts[0] = toupper(ts[0]);
        std::cout << ts[0] << std::endl;
        for(char &c:ts)
        c = toupper(c);
    }
    std::cout << ts << std::endl;
    return;

    while(std::getline(std::cin,s))
        if(!s.empty())
        {
            std::cout << s << std::endl;
            std::cout <<s.size()<<std::endl;
        }
        else
            std::cout << "empty";
}
int main ()
{
    test_vector();
    test_whilecin();
    Sales_data data1, data2;
    double price = 0;
    std::cin >> data1.bookNo >> data1.units_sold >> price ;
    data1.revenue = data1.units_sold * price  ;
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;
    std::cout << data1.revenue << std::endl;
    if (data1.bookNo == data2.bookNo)
    {
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt
        << " " << totalRevenue << " ";
        if (totalCnt != 0)
            std::cout << totalRevenue/totalCnt << std::endl;
        else
            std::cout << "no Sales!" << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Data must refer to the same ISBN" << std::endl;
        return -1;
    }
    test_cstr();
    test_const();
    test_ptr1();
    test_ptr2();
    //int &refval2; //error must be initializer
    //int &refVal4 = 10; //error, rvalue reference
    //double dval = 3.14;
    //int &refVal5 = dval; //error, int ref refer to double, not allow
    int i, &ri = i;
    int *ip1, *ip2; // both ip1 and ip2 are pointers to int
    double dp, *dp2; // dp2 is a pointer to double; dp is a double
    int ival = 42;
    int *p = &ival; // p holds the address of ival; p is a pointer to ival
    Sales_item total;
    if(std::cin >> total)
    {
        Sales_item trans;
        while(std::cin >> trans)
        {
            if(total.isbn()==trans.isbn())
                total += trans;
            else
            {
                std::cout << total << std::endl;//
                total = trans;
            }
        }
        std::cout << total << std::endl;
    }
    else
    {
        std::cerr << "No Data?!" << std::endl;
        return -1;
    }
    unsigned char uc = -1; // For example,
                            //an 8-bit unsigned char can hold values from 0 through
                            //255, inclusive. If we assign a value outside this range, the compiler assigns the
                            //remainder of that value modulo 256. Therefore, assigning –1 to an 8-bit
                            //unsigned char gives that object the value 255
    std::cout << uc << std::endl;
    return 0;
}
