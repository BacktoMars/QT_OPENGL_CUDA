#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtGui/QMainWindow>
#include <QtWidgets/QMainWindow>
//#include <QMenuBar>
//#include <QAction>
//#include <QApplication>
#include "appglwidget.h"
#include "mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private:

        AppGLWidget *w;
};

#endif // MAINWINDOW_H
