#include "Sales_data.h"
#include <iostream>
double Sales_data::avg_price() const
{
    if (units_sold > 0)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    revenue +=  rhs.revenue;
    units_sold += rhs.units_sold;
    return *this;
}

std::istream &read(std::istream &is,Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold*price;
    return is;
}
std::ostream &print(std::ostream &os,const Sales_data &item )
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << std::endl;
    return os;

}

Sales_data &add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum; // return sum will be copied? otherwise should be destroy?
}

Sales_data::Sales_data(std::istream &is)
{
read(is, *this); // read will read a transaction from is into this object
}


std::ostream &operator<<(std::ostream &os,const Sales_data &item)
{
    os << item.isbn()  << " " << item.get_sold() << " "
    << item.get_rev() << " " << item.get_avg();
    return os;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();
    return is;
}
