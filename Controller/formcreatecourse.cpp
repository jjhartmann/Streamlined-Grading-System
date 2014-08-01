/* Contain functions for the createCourse form */

#include "Controller/formcreatecourse.h"
#include "ui_formcreatecourse.h"

FormCreateCourse::FormCreateCourse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateCourse)
{
    ui->setupUi(this);
    this->setWindowTitle("Course Creation Window");
}

FormCreateCourse::~FormCreateCourse()
{
    delete ui;
}

void FormCreateCourse::on_pushButton_cancel_clicked()
{
    this->close();
    emit signalBurronClicked_cancel();
}

void FormCreateCourse::on_pushButton_create_clicked()
{
    QString courseName = ui->lineEdit_courseName->text();
    QString courseNumber = ui->lineEdit_courseNumber->text();
    QString startDate = ui->dateEdit_startDate->text();
    QString endDate = ui->dateEdit_endDate->text();

    QString instructorEID = ui->lineEdit_instructorID->text();

    if(courseName != 0 && courseNumber != 0 && startDate != 0 && endDate !=0)
    {
        this->close();
        emit signalButtonClicked_create(courseName, courseNumber, startDate, endDate, instructorEID);
    }
    else
    {
        ui->label_warning->setText("<font color='red'>Please fill in all * fields.</font>");
    }
}



