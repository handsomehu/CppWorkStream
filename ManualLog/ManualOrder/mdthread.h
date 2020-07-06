#ifndef MDTHREAD_H
#define MDTHREAD_H

#include <QObject>
#include <QThread>
#include "qmd.h"

class MdThread : public QThread
{
	Q_OBJECT

public:
	MdThread(QObject *parent);
	~MdThread();
    QMd *md;
	void run();

public:


private:
	
};

#endif // MDTHREAD_H
