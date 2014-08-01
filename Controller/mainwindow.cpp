#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // *******************************************
    // Destructor for GUI Forms!!
    // Make sure to delete all memory allocation
    if (InstructorWindow != NULL){
        delete InstructorWindow;
    }



}

void MainWindow::on_pushButton_clicked()
{
    InstructorWindow = new FormInstructor;
    InstructorWindow->show();
}
