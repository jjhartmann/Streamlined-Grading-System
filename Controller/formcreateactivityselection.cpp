/* Contains functions for the createActivitySelection form */

#include "Controller/formcreateactivityselection.h"
#include "ui_formcreateactivityselection.h"

FormCreateActivity::FormCreateActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateActivity)
{
    ui->setupUi(this);
}

FormCreateActivity::~FormCreateActivity()
{
    delete ui;
}

void FormCreateActivity::initFormCreateAcitivity(QString username)
{
    ui->label_username->setText(username);
}

void FormCreateActivity::on_pushButton_createEssay_clicked()
{
    emit signal_formCreateActivity_CreateEssay();
}

void FormCreateActivity::on_pushButton_createProblemSet_clicked()
{
    emit signal_formCreateActivity_CreateProblemSet();
}

void FormCreateActivity::on_pushButton_createMultipleChoice_clicked()
{
    emit signal_formCreateActivity_CreateMultipleChoice();
}

void FormCreateActivity::on_pushButton_createCodinAssignment_clicked()
{
    emit signal_formCreateActivity_CreateCodingAssign();
}

void FormCreateActivity::on_pushButton_cancel_clicked()
{
    emit signal_formCreateActivity_CancelClicked();
}
