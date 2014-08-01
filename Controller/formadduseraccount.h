#ifndef FORMADDUSERACCOUNT_H
#define FORMADDUSERACCOUNT_H

#include <QWidget>

namespace Ui {
class FormAddUserAccount;
}

class FormAddUserAccount : public QWidget
{
    Q_OBJECT

public:
    explicit FormAddUserAccount(QWidget *parent = 0);
    ~FormAddUserAccount();

signals:
    void signal_pushbutton_doneDeleteMe();
    void signal_pushbutton_createUserClick(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                           bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin);

private slots:
    void on_cancelAccount_clicked();

    void on_createAccount_clicked();

private:
    Ui::FormAddUserAccount *ui;
};

#endif // FORMADDUSERACCOUNT_H
