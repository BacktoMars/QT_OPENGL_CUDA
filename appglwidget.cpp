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
  
	spbo.initCuda();

  glClearColor(0, 0.5, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	printf("initCuda called.\n");

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

	//printf("XSize = %d YSize = %d\n", XSize, YSize);
	//
	//GLfloat x, y;

	//glLoadIdentity();
	//glBegin(GL_POINTS);
	//for (int i=0; i<XSize; i++)
	//	for (int j=0; j<YSize; j++)
	//	{
	//		x = (GLfloat)i/XSize*2. - 1.0;
	//		y = (GLfloat)j/YSize*2. - 1.0;
	//		//glColor3fv(color);
	//		glColor3f(1./(double)XSize*(double)i, 0.0f, 1./(double)YSize*(double)j*2.);
	//		glVertex2f(x, y);
	//	}
	//glEnd();
	//glFlush();
	//glutSwapBuffers();

    //glLoadIdentity();
    //qglColor( Qt::white );
    //glBegin(GL_TRIANGLES);
    //glVertex3f( 0.0f, 1.0f, 0.0f);
    //glVertex3f(-1.0f,-1.0f, 0.0f);
    //glVertex3f( 1.0f,-1.0f, 0.0f);
    //glEnd();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); //Select The Modelview Matrix
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);

	spbo.runCuda( 10 );
	printf("runCuda executed.\n");
	// now bind buffer after cuda is done
	spbo.bind();

	printf("pbo binded.\n");

  glBegin(GL_QUADS);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-1.0f,-1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-1.0f,1.0f,-1.0f);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(1.0f,1.0f,-1.0f);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();

	spbo.release();
}

void AppGLWidget::resizeGL(int w, int h)
{
    h = h < 1 ? 1 : h;
    glViewport( 0, 0, (GLint)w, (GLint)h );
	//spbo.resize(w, h);

  glEnable(GL_TEXTURE_2D);
  spbo.resize(w, h);
  //glMatrixMode(GL_PROJECTION); //Select The Projection Matrix
  //glLoadIdentity(); //Reset The Projection Matrix

  //glMatrixMode(GL_MODELVIEW); //Select The Modelview Matrix
  //glLoadIdentity(); //Reset The Modelview Matrix

}
