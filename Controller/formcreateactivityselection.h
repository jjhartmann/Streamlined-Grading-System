#ifndef FORMCREATEACTIVITY_H
#define FORMCREATEACTIVITY_H

#include <QWidget>

namespace Ui {
class FormCreateActivity;
}

class FormCreateActivity : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreateActivity(QWidget *parent = 0);
    ~FormCreateActivity();
    //INIT
    void initFormCreateAcitivity(QString username);


signals:
    void signal_formCreateActivity_CancelClicked();
    void signal_formCreateActivity_CreateProblemSet();
    void signal_formCreateActivity_CreateEssay();
    void signal_formCreateActivity_CreateMultipleChoice();
    void signal_formCreateActivity_CreateCodingAssign();


private slots:
    void on_pushButton_createEssay_clicked();

    void on_pushButton_createProblemSet_clicked();

    void on_pushButton_createMultipleChoice_clicked();

    void on_pushButton_createCodinAssignment_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::FormCreateActivity *ui;
};

#endif // FORMCREATEACTIVITY_H
