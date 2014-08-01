/* Contain functions for the accountTypeSelection form */

#include "Controller/formselectmultipleaccounts.h"
#include "ui_formselectmultipleaccounts.h"

FormSelectMultipleAccounts::FormSelectMultipleAccounts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSelectMultipleAccounts)
{
    ui->setupUi(this);
    this->setWindowTitle("Account Type Selection");
}

FormSelectMultipleAccounts::~FormSelectMultipleAccounts()
{
    delete ui;
}

void FormSelectMultipleAccounts::initializeGui(QVector<QString> *accountVector){
    ui->pushButton_instructor->hide();
    ui->pushButton_TATM->hide();
    ui->pushButton_adminAssist->hide();
    ui->pushButton_academicAdmin->hide();
    ui->pushButton_sysAdmin->hide();

    //Construct GUI

    int vSize = accountVector->size();
    for(int i = 0; i < vSize; i++){
        QString type = accountVector->at(i);
        if(type == "INSTRUCTOR"){
            ui->pushButton_instructor->show();
        } else if(type == "TASSISTENT"){
            ui->pushButton_TATM->show();
        } else if(type == "ASSISTENTA"){
            ui->pushButton_adminAssist->show();
        } else if(type == "ACEDEMICADMN"){
            ui->pushButton_academicAdmin->show();
        } else if(type == "SYSTEMADMN"){
            ui->pushButton_sysAdmin->show();
        }

    }

}

void FormSelectMultipleAccounts::on_pushButton_instructor_clicked()
{
    this->close();
    emit signal_pushbutton_InstructorClick();
}

void FormSelectMultipleAccounts::on_pushButton_TATM_clicked()
{
    this->close();
    emit signal_pushbutton_TATMClick();
}

void FormSelectMultipleAccounts::on_pushButton_adminAssist_clicked()
{
    this->close();
    emit signal_pushbutton_AdminAssistantClick();
}

void FormSelectMultipleAccounts::on_pushButton_academicAdmin_clicked()
{
    this->close();
    emit signal_pushbutton_AcademicAdminClick();
}



void FormSelectMultipleAccounts::on_pushButton_sysAdmin_clicked()
{
    this->close();
    emit signal_pushbutton_SysAdminClick();
}
