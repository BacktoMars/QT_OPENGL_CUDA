#include "test1.h"

test1::test1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	printf("test1 set up\n");
	launch_kernel();
}

test1::~test1()
{

}
