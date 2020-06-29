#ifndef QTD_H
#define QTD_H
#include <QObject>
#include "tradewrapper.h"

class QTd: public QObject , public TradeWrapper
{
public:
    QTd(const std::string &path);
};

#endif // QTD_H
