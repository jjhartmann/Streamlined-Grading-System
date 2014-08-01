#ifndef SYSADMINVIEW_H
#include "Controller/controllermodelinterface.h"
#include "formadduseraccount.h"
#include "Model/modeldatainterface.h"
#define SYSADMINVIEW_H

#include <QMainWindow>
#include <QMessageBox>


namespace Ui {
class SysAdminView;
}

class SysAdminView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SysAdminView(QWidget *parent = 0);
    ~SysAdminView();

    void initSysAdminGui(QString username, QString eID);

signals:
    void signal_sysAdminLogOff();

private slots:
    void on_addUserAccount_clicked();
    void on_deleteAccount_clicked();
    void on_modifyAccount_clicked();\

    //SLOTS FOR ADD USER ACCOUNT
    void slot_addUserAccount_done();
    void slot_addUserAccount_createAccountClick(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                                bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin);


    void on_tableView_UserAccounts_doubleClicked(const QModelIndex &index);



    void on_actionLog_Out_triggered();

private:
    //Vars
    QString sysAdminUsername;
    QString sysAdminEmployeeID;
    QString UserName;
    QString getpassword;
    bool currentckbsAdminSys;
    bool currentckbxAcademicAdmin;
    bool currentckbxInstructor;
    bool currentckbxAdminAssist;
    bool currentckbsTATM;

    //Functions
    Ui::SysAdminView *ui;
    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;
    FormAddUserAccount *addform;
    QSqlQueryModel *accountModel;
    ModelDataInterface model;
    void refreshList();
};

#endif // SYSADMINVIEW_H
