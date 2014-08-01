/* Contains functions or the changePassword form */

#include "Controller/formchangepassword.h"
#include "ui_formchangepassword.h"

FormChangePassword::FormChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChangePassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Change Password Window");
    interface = new ControllerModelInterface;
    this->setWindowTitle("Change Password Window");
}

FormChangePassword::~FormChangePassword()
{
    delete ui;
    delete interface;
}

void FormChangePassword::setUsername(QString user){
    username = user;
}

void FormChangePassword::on_cancel_clicked()
{
    this->close();
    emit cancelClicked();

}

void FormChangePassword::on_submit_clicked()
{
    QString newpassword = ui->lineEdit_newpassword->text();
    QString retypepassword = ui->lineEdit_retypepassword->text();

    if (newpassword == retypepassword){
        interface->changePassword(newpassword, username);
        this->close();
        emit selectClicked();
    } else {
        QMessageBox box;
        box.setText("Passwords did not match");
        box.exec();
    }

}

