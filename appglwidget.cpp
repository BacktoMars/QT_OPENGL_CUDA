#include "appglwidget.h"

AppGLWidget::AppGLWidget(QWidget *parent)
	: QGLWidget(parent)
{

	launch_kernel();
	printf("Kernel launched!\n");
}

AppGLWidget::~AppGLWidget()
{

}
