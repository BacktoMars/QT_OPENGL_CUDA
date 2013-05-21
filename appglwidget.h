#ifndef APPGLWIDGET_H
#define APPGLWIDGET_H

#include <QGLWidget>

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

};


extern "C" void launch_kernel();

#endif // APPGLWIDGET_H
