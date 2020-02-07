#include "bs_date.h"
using namespace BsChrono;

Date::Date(int dd, Month mm, int yy)
:d{dd}, m{static_cast<int>(mm)}, y{yy}
{
//if (y == 0) y = default_date().year();
//if (m == static_cast<int>(Month{})) m = static_cast<int>(default_date().month());
//if (d == 0) d = default_date().day();
//if (!is_valid()) throw Bad_date();
}

bool Date::is_valid()
{
    return is_date(d,static_cast<Month>(m),y);
}

inline int Date::day() const
{
    return d;
}

Date& Date::add_month(int n)
{
    if (n==0)
        return *this;
    if (n>0)
    {
        int delta_y = n/12; // number of whole years
        int mm = static_cast<int>(m)+n%12; // number of months ahead
        if (12 < mm)
        { // note: dec is represented by 12
            ++delta_y;
            mm -= 12;
        }
    // ... handle the cases where the month mm doesn’t have day d ...
        y += delta_y;
        m = mm;
        return *this;
    }
    // ... handle negative n ...
    return *this;
}

bool BsChrono::is_date(int d, Month m, int y)
{
    int ndays;
    switch (m)
    {
        case Month::feb:
        //ndays = 28+is_leapyear(y);
        break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
        ndays = 30;
        break;
        case Month::jan: case Month::mar: case Month::may: case Month::jul:
        case Month::aug: case Month::oct: case Month::dec:
        ndays = 31;
        break;
        default:
        return false;
    }
    return 1<=d && d<=ndays;
}

const Date& BsChrono::default_date()
{
    static Date d {1,Month::jan,1970};
    return d;
}

inline bool operator==(Date a, Date b) // equality
{
    return a.day()==b.day() && a.month()==b.month() && a.year()==b.year();
}
