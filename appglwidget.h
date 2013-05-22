#ifndef APPGLWIDGET_H
#define APPGLWIDGET_H

#include <QGLWidget>
#include "SimplePBO.h"

class AppGLWidget : public QGLWidget
{
    Q_OBJECT

    public:
        AppGLWidget(QWidget *parent);
        ~AppGLWidget();
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
    private:

		int XSize;
		int YSize;
		SimplePBO spbo;
};


extern "C" void launch_kernel();

#endif // APPGLWIDGET_H
