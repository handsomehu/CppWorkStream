#include "Sales_data.h"

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
