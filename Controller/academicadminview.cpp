/* Codes of functions for the main UI and related actions for academic administrator */

#include "Controller/academicadminview.h"
#include "ui_academicadminview.h"

AcademicAdminView::AcademicAdminView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AcademicAdminView)
{
    ui->setupUi(this);


    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface;
    this->setWindowTitle("Academic Administrator Main Window");
}

AcademicAdminView::~AcademicAdminView()
{
    delete ui;
    delete interface;

}

// Emit signal when the log off button is clicked
void AcademicAdminView::on_actionLog_off_triggered()
{
    emit signal_academicAdminLogOff();
}
