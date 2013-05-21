#include "mainwindow.h"

    MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    w=new AppGLWidget(this);
    setCentralWidget(w);

    QMenu *fileMenu = new QMenu("&File");
    fileMenu->addAction("&Close", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);
    menuBar()->addMenu(fileMenu);
}

MainWindow::~MainWindow()
{

}
