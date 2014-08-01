#ifndef FORMSELECTMULTIPLEACCOUNTS_H
#define FORMSELECTMULTIPLEACCOUNTS_H

#include <QWidget>

namespace Ui {
class FormSelectMultipleAccounts;
}

class FormSelectMultipleAccounts : public QWidget
{
    Q_OBJECT

public:
    explicit FormSelectMultipleAccounts(QWidget *parent = 0);
    ~FormSelectMultipleAccounts();
    void initializeGui(QVector<QString> *accountVector);

signals:
    void signal_pushbutton_InstructorClick();
    void signal_pushbutton_TATMClick();
    void signal_pushbutton_AcademicAdminClick();
    void signal_pushbutton_AdminAssistantClick();
    void signal_pushbutton_SysAdminClick();

private slots:


    void on_pushButton_instructor_clicked();

    void on_pushButton_TATM_clicked();

    void on_pushButton_adminAssist_clicked();

    void on_pushButton_academicAdmin_clicked();

    void on_pushButton_sysAdmin_clicked();

private:
    Ui::FormSelectMultipleAccounts *ui;

    //Functions

};

#endif // FORMSELECTMULTIPLEACCOUNTS_H
