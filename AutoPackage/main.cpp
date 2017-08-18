#include "AutoPackage.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoPackage w;
	w.show();
	return a.exec();
}
