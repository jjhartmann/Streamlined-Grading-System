/* Contain functions for systemAdministrator main window and related actions */

#include "Controller/sysadminview.h"
#include "ui_sysadminview.h"

SysAdminView::SysAdminView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysAdminView)
{
    ui->setupUi(this);

    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface();
    this->setWindowTitle("System Administrator Window");
    ui->tableView_UserAccounts->setSelectionBehavior(QAbstractItemView::SelectRows);

}

SysAdminView::~SysAdminView()
{
    delete ui;
    delete interface;

    accountModel->clear();

    if(accountModel != NULL){
        accountModel->clear();
        accountModel->deleteLater();
    }

}

void SysAdminView::initSysAdminGui(QString username, QString eID)
{

    //INIT THE GUI
    sysAdminUsername = username;
    sysAdminEmployeeID = eID;
    ui->label_NameDisplay->setText(sysAdminUsername);
    refreshList();
}

void SysAdminView::on_addUserAccount_clicked()
{
    addform = new FormAddUserAccount;
    addform->show();
    //Connections...
    connect(addform, SIGNAL(signal_pushbutton_doneDeleteMe()), this, SLOT(slot_addUserAccount_done()));
    connect(addform, SIGNAL(signal_pushbutton_createUserClick(QString,QString,QString,QString,QString,bool,bool,bool,bool,bool)),
            this, SLOT(slot_addUserAccount_createAccountClick(QString,QString,QString,QString,QString,bool,bool,bool,bool,bool)));
    refreshList();
}

void SysAdminView::on_deleteAccount_clicked()
{
    int row = -1;
    row = ui->tableView_UserAccounts->selectionModel()->currentIndex().row();
    if(row != -1)
    {
        QString employeeID = ui->tableView_UserAccounts->model()->index(row, 1).data().toString();
        interface->deleteAccount(employeeID);

        //Refresh System
        refreshList();
    }
}


void SysAdminView::on_modifyAccount_clicked()
{
    QString blockStatus;
    interface->sysadminModifyAccount(
                ui->lineEdit_eID->text(),
                ui->lineEdit_username->text(),
                ui->lineEdit_firstname->text(),
                ui->lineEdit_lastname->text(),
                ui->checkBox_instructor->isChecked(),
                ui->checkBox_TA->isChecked(),
                ui->checkBox_acaAdmin->isChecked(),
                ui->checkBox_adminAssist->isChecked(),
                ui->checkBox_sysadmin->isChecked(),
                currentckbxInstructor, currentckbsTATM,
                currentckbxAcademicAdmin, currentckbxAdminAssist,
                currentckbsAdminSys);
    if (ui->checkBox_blockStatus->isChecked() == false){
        blockStatus = "0";
    }
    else{
        blockStatus = "1";
    }
    QString getblockstatus = model.getDatabaseInstance("Account", "UserName", "BlockStatus", UserName);
    if (getblockstatus == "1" && blockStatus == "0")
    {
        model.updateDatabaseInstance("Account", "LoginAttempts", "UserName", UserName, "0");
    }
    model.updateDatabaseInstance("Account", "BlockStatus", "UserName", UserName, blockStatus);

    QString currentpassword = ui->lineEdit_password->text();
    if (getpassword != currentpassword){
        model.updateDatabaseInstance("Account", "password", "UserName", UserName, ui->lineEdit_password->text());
        model.updateDatabaseInstance("Account", "passwordFlag", "UserName", UserName, "1");
    }


    //Refresh the tableview
    refreshList();
}


void SysAdminView::on_tableView_UserAccounts_doubleClicked(const QModelIndex &index)
{
    //RESET ACCOUNT STATUS
    currentckbsAdminSys = false;
    currentckbsTATM = false;
    currentckbxAcademicAdmin = false;
    currentckbxAdminAssist = false;
    currentckbxInstructor = false;
    UserName = ui->tableView_UserAccounts->model()->index(index.row(), 0).data().toString();
    ModelDataInterface dataModel("getpassword");
    getpassword = dataModel.getDatabaseInstance("Account", "UserName", "password", UserName);

    ui->checkBox_sysadmin->setChecked(false);
    ui->checkBox_adminAssist->setChecked(false);
    ui->checkBox_acaAdmin->setChecked(false);
    ui->checkBox_instructor->setChecked(false);
    ui->checkBox_TA->setChecked(false);
    ui->lineEdit_eID->setText(ui->tableView_UserAccounts->model()->index(index.row(), 1).data().toString());
    ui->lineEdit_username->setText(ui->tableView_UserAccounts->model()->index(index.row(), 0).data().toString());
    ui->lineEdit_firstname->setText(ui->tableView_UserAccounts->model()->index(index.row(), 2).data().toString());
    ui->lineEdit_lastname->setText(ui->tableView_UserAccounts->model()->index(index.row(), 3).data().toString());
    ui->lineEdit_password->setText(getpassword);


    QVector<QString> *accountTypes = interface->getMultipleAccounts(UserName);
    int typesize = accountTypes->size();

    for(int i = 0; i < typesize; i++)
    {
        if(accountTypes->at(i) == "SYSTEMADMN")
        {
            ui->checkBox_sysadmin->setChecked(true);
            currentckbsAdminSys = true;
        }
        if(accountTypes->at(i) == "ASSISTENTA")
        {
            ui->checkBox_adminAssist->setChecked(true);
            currentckbxAdminAssist = true;
        }
        if(accountTypes->at(i) == "ACEDEMICADMN")
        {
            ui->checkBox_acaAdmin->setChecked(true);
            currentckbxAcademicAdmin = true;
        }
        if(accountTypes->at(i) == "INSTRUCTOR")
        {
            ui->checkBox_instructor->setChecked(true);
            currentckbxInstructor = true;
        }
        if(accountTypes->at(i) == "TASSISTENT")
        {
            ui->checkBox_TA->setChecked(true);
            currentckbsTATM = true;
        }
    }
    QString dblock = model.getDatabaseInstance("Account", "UserName", "BlockStatus", UserName);
    if(dblock == "0")
    {
        ui->checkBox_blockStatus->setChecked(false);
    }
    if(dblock == "1")
    {
        ui->checkBox_blockStatus->setChecked(true);
    }
}


//ADD USER ACCOUNTS FORM SLOTS
void SysAdminView::slot_addUserAccount_done()
{
    addform->close();
    if(addform != NULL){
       addform->deleteLater();
    }
}

void SysAdminView::slot_addUserAccount_createAccountClick(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                                          bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin)
{

    interface->sysadminCreateAccount(employeeID, username, password, firstname, lastname, chkbxInstructor, chkbxTA, chkbxAcademicAdmin, chkbxAdminAssistant, chkbxSysAdmin);
    //Hide Add form when not in use
    addform->close();
    if(addform != NULL){
       addform->deleteLater();
    }
    refreshList();
}

//**************************************
//PRIVATE FUNCTIONS
// Show/refresh table view in main UI
void SysAdminView::refreshList(){
    // ModelDataInterface *dataInterface = new ModelDataInterface();
    accountModel = interface->getUserAccounts();
    ui->tableView_UserAccounts->setModel(accountModel);
}



void SysAdminView::on_actionLog_Out_triggered()
{
    emit signal_sysAdminLogOff();
}
