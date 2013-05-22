//#include "test1.h"
//#include <QtWidgets/QApplication>
#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include "mainform.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//test1 w;
	//MainWindow w;
 //   w.show();
    MainForm w;
    w.show();
	return a.exec();
}
