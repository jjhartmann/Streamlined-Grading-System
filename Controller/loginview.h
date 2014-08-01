#ifndef LOGINVIEW_H
#include "formchangepassword.h"
#include "formselectmultipleaccounts.h"
#define LOGINVIEW_H
#include "Model/modeldatainterface.h"

#include <QMainWindow>



namespace Ui {
class LoginView;
}

class LoginView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = 0);
    ~LoginView();


signals:
    void signalShowAccountInstructor(QString username, QString eID);
    void signalShowAccountTATM(QString username, QString eID);
    void signalShowAccountAdminAssistant(QString username, QString eID);
    void signalShowAccountAcademicAdmin(QString username, QString eID);
    void signalShowAccountSysAdmin(QString username, QString eID);
    void signalquitLoginView();


private slots:
    void on_LoginButton_clicked();
    void changepasswordFormCancel();
    void changepasswordFormSelect();

    void on_pushButton_clicked();

    // SLOTS FOR Select Account Type Form
    void slot_pushbutton_InstructorClick();
    void slot_pushbutton_TATMClick();
    void slot_pushbutton_AcademicAdminClick();
    void slot_pushbutton_AdminAssistantClick();
    void slot_pushbutton_SysAdminClick();

    void on_pushButton_password_clicked();

private:
    //Varibles and Objects
    Ui::LoginView *ui;
    FormChangePassword *cform;
    QString password;
    QString username;
    QString employeeID;
    ModelDataInterface model;



    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;
    FormSelectMultipleAccounts *selectAccountView;


    //Functions
    void delete_selectAccountView();
    void displayChoices(QString username);
    void openAccountView(int accountType);
    void checkOpenAccountLogic(QString password, QString username);
    void checkpasswordlogic(QString password, QString username);
    //To Do:
    //BLOCKING ACCOUNTS
};

#endif // LOGINVIEW_H
