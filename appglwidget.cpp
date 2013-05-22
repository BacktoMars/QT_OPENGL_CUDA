#include <stdio.h>
#include "appglwidget.h"

#if defined __APPLE__ || defined __linux
#include <GL/glut.h>
#else
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <glut.h>
#endif


    AppGLWidget::AppGLWidget(QWidget *parent)
: QGLWidget(parent)
{

    //launch_kernel();
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

	glClearColor(.3, .3, .3, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	QSize glSize = this->frameSize();
	XSize = glSize.width();
	YSize = glSize.height();

	//XSize = 2000;
	//YSize = 2000;

	printf("XSize = %d YSize = %d\n", XSize, YSize);
	
	GLfloat x, y;

	glLoadIdentity();
	glBegin(GL_POINTS);
	for (int i=0; i<XSize; i++)
		for (int j=0; j<YSize; j++)
		{
			x = (GLfloat)i/XSize*2. - 1.0;
			y = (GLfloat)j/YSize*2. - 1.0;
			//glColor3fv(color);
			glColor3f(1./(double)XSize*(double)i, 0.0f, 1./(double)YSize*(double)j*2.);
			glVertex2f(x, y);
		}
	glEnd();
	glFlush();
	//glutSwapBuffers();

    //glLoadIdentity();
    //qglColor( Qt::white );
    //glBegin(GL_TRIANGLES);
    //glVertex3f( 0.0f, 1.0f, 0.0f);
    //glVertex3f(-1.0f,-1.0f, 0.0f);
    //glVertex3f( 1.0f,-1.0f, 0.0f);
    //glEnd();
}

void AppGLWidget::resizeGL(int w, int h)
{
    h = h < 1 ? 1 : h;
    glViewport( 0, 0, (GLint)w, (GLint)h );
}
