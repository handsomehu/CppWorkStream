#include "ctp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ctp w;
	w.show();
	return a.exec();
}
