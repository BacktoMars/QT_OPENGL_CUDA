#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "appglwidget.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_RUNCUDA_clicked();
	//void on_pushButton_EXIT_clicked();

private:
    AppGLWidget *glWidget;
    Ui::MainForm *ui;
};

//extern "C" void launch_kernel();

#endif // MAINFORM_H
