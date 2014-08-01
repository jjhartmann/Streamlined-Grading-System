/* Contains functions for the assignInstructor form */

#include "Controller/formassigninstructortocourse.h"
#include "ui_formassigninstructortocourse.h"

FormAssignInstructortoCourse::FormAssignInstructortoCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAssignInstructortoCourse)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Instructor");
}

FormAssignInstructortoCourse::~FormAssignInstructortoCourse()
{
    delete ui;
}

void FormAssignInstructortoCourse::on_pushButton_assignInstructor_clicked()
{
    QString instructorEID = ui->lineEdit_instructorID->text();

    this->close();
    emit signalassignButtonClicked(instructorEID);
}

void FormAssignInstructortoCourse::on_pushButton_cancel_clicked()
{
    this->close();
    emit signalcancelButtonClicked();
}
