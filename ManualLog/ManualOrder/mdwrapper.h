#ifndef MDWRAPPER_H
#define MDWRAPPER_H
#include <iostream>
#include "./libhead/ThostFtdcMdApi.h"


class MdWrapper : public CThostFtdcMdSpi
{
public:
    MdWrapper(const std::string &path);
};

#endif // MDWRAPPER_H
