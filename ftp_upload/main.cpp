#include "ftp_upload.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ftp_upload w;
	w.show();
	return a.exec();
}
