#include "basic_type.h"
#include "token_stream.h"

extern Token_stream ts;
extern std::map<std::string,double> table;
extern int no_of_errors;

double expr(bool);
double prim(bool get) // handle primar ies
{
    if (get)
        ts.get(); // read next token
    switch (ts.current().kind)
    {
        case Kind::number: // floating-point constant
        {
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name:
        {
            double& v = table[ts.current().string_value]; // find the corresponding
            if (ts.get().kind == Kind::assign)
                v = expr(true); // ’=’ seen: assignment
            return v;
        }
        case Kind::minus: // unar y minus
            return -prim(true);
        case Kind::lp:
        {
            auto e = expr(true);
            if (ts.current().kind != Kind::rp)
                return error(std::string(") expected"));
            ts.get(); // eat ’)’
            return e;
        }
        default:
            return error("primar y expected");
    }
}
double term(bool get) // multiply and divide
{
    double left = prim(get);
    for (;;)
    {
        switch (ts.current().kind)
        {
            case Kind::mul:
                left *= prim(true);
                break;
            case Kind::div:
                if (auto d = prim(true))
                {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
            }
    }
}
double expr(bool get) // add and subtract
{
    double left = term(get);
    for (;;)
    { // ‘‘forever’’
        switch (ts.current().kind)
        {
        case Kind::plus:
            left += term(true);
            break;
        case Kind::minus:
            left -= term(true);
            break;
        default:
            return left;
        }
    }
}

double error(const std::string& s)
{
    no_of_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

void calculate()
{
    for (;;)
    {
        ts.get();
        if (ts.current().kind == Kind::end)
            break;
        if (ts.current().kind == Kind::print)
            continue;
        std::cout << expr(false) << '\n';
    }
}
