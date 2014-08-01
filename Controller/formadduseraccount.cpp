#include "Controller/formadduseraccount.h"
#include "ui_formadduseraccount.h"

#include <QMessageBox>

FormAddUserAccount::FormAddUserAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAddUserAccount)
{
    ui->setupUi(this);
    this->setWindowTitle("Add User Account");
}

FormAddUserAccount::~FormAddUserAccount()
{
    delete ui;
}

void FormAddUserAccount::on_cancelAccount_clicked()
{
    emit signal_pushbutton_doneDeleteMe();
}

void FormAddUserAccount::on_createAccount_clicked()
{

    QString employeeID = ui->lineEdit_eID->text();
    QString userName = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString firstName = ui->lineEdit_firstname->text();
    QString lastName = ui->lineEdit_lastname->text();
    bool chkInstructor = ui->checkBox_instructor->isChecked();
    bool chkTA = ui->checkBox_TA->isChecked();
    bool chkAcademicAdmin = ui->checkBox_acaAdmin->isChecked();
    bool chkAdminAssist = ui->checkBox_adminAssist->isChecked();
    bool chkSysAdmin = ui->checkBox_sysadmin->isChecked();

    if(employeeID != 0 && userName != 0 && password != 0 && firstName != 0 && lastName !=0)
    {
        //MORE Error corrections (different class?)
        emit signal_pushbutton_createUserClick(employeeID, userName, password, firstName, lastName, chkInstructor, chkTA, chkAcademicAdmin, chkAdminAssist, chkSysAdmin);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("All * field must be filed");
        msgBox.exec();
    }

}
