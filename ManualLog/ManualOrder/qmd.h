#ifndef QMD_H
#define QMD_H
#include <QObject>
#include "mdwrapper.h"

class QMd: public QObject , public MdWrapper
{
public:
    QMd(const std::string &path);
};

#endif // QMD_H
