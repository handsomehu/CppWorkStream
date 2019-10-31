#include "bookdata.h"

// calculate and print the price for the given number of copies, applying any discounts
double print_total(std::ostream &os,
const Quote &item, std::size_t n)
{
// depending on the type of the object bound to the item parameter
// calls either Quote::net_price or Bulk_quote::net_price
double ret = item.net_price(n);
os << "ISBN: " << item.isbn() // calls Quote::isbn
<< " # sold: " << n << " total due: " << ret << std::endl;
return ret;
}

// if the specified number of items are purchased, use the discounted price
double Bulk_quote::net_price(size_t cnt) const
{
if (cnt >= min_qty)
    return cnt * (1 - discount) * price;
else
    return cnt * price;
}
