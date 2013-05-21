#include <stdio.h>
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

void AppGLWidget::initializeGL()
{
    qglClearColor( Qt::black );
}

void AppGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glLoadIdentity();
    qglColor( Qt::white );
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 0.0f);
    glVertex3f( 1.0f,-1.0f, 0.0f);
    glEnd();
}

void AppGLWidget::resizeGL(int w, int h)
{
    h = h < 1 ? 1 : h;
    glViewport( 0, 0, (GLint)w, (GLint)h );
}
