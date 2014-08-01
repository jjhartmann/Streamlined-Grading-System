/* Contain functions for the log-in view */

#include "Controller/loginview.h"
#include "ui_loginview.h"

#include<QMessageBox>

LoginView::LoginView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
    this->setWindowTitle("Log-In Window");

    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface;
}

LoginView::~LoginView()
{
    delete ui;
    delete interface;

}


// When the User enters in credentials, this functions process the login details.
void LoginView::on_LoginButton_clicked()
{
    QMessageBox msgBox;
    password = ui->passwordLogin->text();
    username = ui->usernameLogin->text();
    ui->usernameLogin->setText("");
    ui->passwordLogin->setText("");

    if(password != NULL && username != NULL){
        checkOpenAccountLogic(password, username);
    } else {
        msgBox.setText("Enter your username and password");
        msgBox.exec();
    }
}


//***********************************
// PRIVATE SLOTS:: EMITED FROM CHOOSE ACCOUNT TYPE
//Choose account type view
void LoginView::slot_pushbutton_InstructorClick(){
    delete_selectAccountView();
    openAccountView(1);
}

void LoginView::slot_pushbutton_TATMClick(){
    delete_selectAccountView();
    openAccountView(2);
}

void LoginView::slot_pushbutton_AdminAssistantClick(){
    delete_selectAccountView();
    openAccountView(3);
}

void LoginView::slot_pushbutton_AcademicAdminClick(){
    delete_selectAccountView();
    openAccountView(4);
}

void LoginView::slot_pushbutton_SysAdminClick(){
    delete_selectAccountView();
    openAccountView(5);
}


//**********************************
//Change password for first time log-in user form view
void LoginView::changepasswordFormCancel(){
    if(cform != NULL){
       cform->deleteLater();
    }
}

void LoginView::changepasswordFormSelect(){
    if(cform != NULL){
         cform->deleteLater();
    }
}




//************************************
// Private Functions

void LoginView::checkOpenAccountLogic(QString password, QString username){
    QMessageBox msgBox;
    bool accepted = false;
    bool multiAccount = false;
    bool passwordFlag = false;
    int accountType;
    QString blocked;
    int counter;
    QString getloginattempts;

    ModelDataInterface dataModel1("connnectionGetBlocked");
    blocked = dataModel1.getDatabaseInstance("Account", "UserName", "BlockStatus", username);
    ModelDataInterface dataModel2("connnectionGetLoginAttempts");
    getloginattempts = dataModel2.getDatabaseInstance("Account", "UserName", "LoginAttempts", username);
    counter = getloginattempts.toInt();
    accepted = interface->checkCredentials(password, username);

    if (blocked == "0")
    {
        if (accepted){
            multiAccount = interface->checkMultipleAccounts(username);
            passwordFlag = interface->checkPasswordFlag(username);
            employeeID = interface->getemployeeID(username);

            // For Initial Login - Change Password
            if (passwordFlag){
                cform = new FormChangePassword;
                connect(cform, SIGNAL(cancelClicked()), this, SLOT(changepasswordFormCancel()));
                connect(cform, SIGNAL(selectClicked()), this, SLOT(changepasswordFormSelect()));
                cform->setUsername(username);

                cform->show();


            }
            else if(multiAccount)
            {
                displayChoices(username);
                ModelDataInterface dataModel("ConnectionUpdateAttempts");
                dataModel.updateDatabaseInstance("Account", "LoginAttempts", "UserName", username, "0");
            }
            else
            {
                accountType = interface->checkAccountType(username);
                ModelDataInterface dataModel("ConnectionUpdateAttempts2");
                dataModel.updateDatabaseInstance("Account", "LoginAttempts", "UserName", username, "0");
                openAccountView(accountType);
            }
        }
        else
        {
            msgBox.setText("Your Username or Password is incorrect.");
            msgBox.exec();
            counter = counter + 1;
            ModelDataInterface dataModel("ConnectionUpdateAttempts3");
            dataModel.updateDatabaseInstance("Account", "LoginAttempts", "UserName", username, QString::number(counter));
            if (counter > 5){
                msgBox.setText("Your account is blocked, too manay attempts, Please contact system administrator.");
                msgBox.exec();
                ModelDataInterface dataModel("ConnectionUpdateAttempts4");
                dataModel.updateDatabaseInstance("Account", "BlockStatus", "UserName", username, "1");
            }
        }
    }
    else if (blocked == "1")
    {
        msgBox.setText("Your account is blocked, Please contact system administrator.");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Your Username or Password is incorrect.");
        msgBox.exec();
    }
}
//PASSWORD INPUT LOOK TO HEADER
void LoginView::checkpasswordlogic(QString password, QString username)
{
    QMessageBox msgBox;
    bool accepted = false;
    bool passwordFlag = false;

    // Check database for proper working credentials
    accepted = interface->checkCredentials(password, username);

    if (accepted){
        passwordFlag = interface->checkPasswordFlag(username);
        cform = new FormChangePassword;
        connect(cform, SIGNAL(cancelClicked()), this, SLOT(changepasswordFormCancel()));
        connect(cform, SIGNAL(selectClicked()), this, SLOT(changepasswordFormSelect()));
        cform->setUsername(username);
        cform->show();
    }
    else{
        msgBox.setText("Your Username or Password is incorrect.");
        msgBox.exec();
    }

}



void LoginView::displayChoices(QString username){
    QVector<QString> *accountVector;
    accountVector = interface->getMultipleAccounts(username);

    selectAccountView = new FormSelectMultipleAccounts();

    //connecstions
    connect(selectAccountView, SIGNAL(signal_pushbutton_AcademicAdminClick()), this, SLOT(slot_pushbutton_AcademicAdminClick()));
    connect(selectAccountView, SIGNAL(signal_pushbutton_AdminAssistantClick()), this, SLOT(slot_pushbutton_AdminAssistantClick()));
    connect(selectAccountView, SIGNAL(signal_pushbutton_InstructorClick()), this, SLOT(slot_pushbutton_InstructorClick()));
    connect(selectAccountView, SIGNAL(signal_pushbutton_SysAdminClick()), this, SLOT(slot_pushbutton_SysAdminClick()));
    connect(selectAccountView, SIGNAL(signal_pushbutton_TATMClick()), this, SLOT(slot_pushbutton_TATMClick()));

    selectAccountView->initializeGui(accountVector);
    selectAccountView->show();

}


void LoginView::openAccountView(int accountType){

    switch(accountType){
    case 1:
        emit signalShowAccountInstructor(username, employeeID);
        break;
    case 2:
        emit signalShowAccountTATM(username, employeeID);
        break;
    case 3:
        emit signalShowAccountAdminAssistant(username, employeeID);
        break;
    case 4:
        emit signalShowAccountAcademicAdmin(username, employeeID);
        break;
    case 5:
        emit signalShowAccountSysAdmin(username, employeeID);
        break;
    }

    // Once a login account has been decided, close the loginscreen.
    this->close();
    emit signalquitLoginView();

}

void LoginView::delete_selectAccountView(){
    if(selectAccountView != NULL){
         selectAccountView->deleteLater();
    }
}


void LoginView::on_pushButton_clicked()
{
    this->close();
    emit signalquitLoginView();
}


// Change password at anytime for user (change password button) from view
void LoginView::on_pushButton_password_clicked()
{
    QMessageBox msgBox;
    password = ui->passwordLogin->text();
    username = ui->usernameLogin->text();
    ui->usernameLogin->setText("");
    ui->passwordLogin->setText("");

    if(password != NULL && username != NULL){
        checkpasswordlogic(password, username);
    } else {
        msgBox.setText("Enter your username and password");
        msgBox.exec();
    }
}
