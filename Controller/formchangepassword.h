#ifndef FORMCHANGEPASSWORD_H
#define FORMCHANGEPASSWORD_H

#include "controllermodelinterface.h"
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class FormChangePassword;
}

class FormChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit FormChangePassword(QWidget *parent = 0);
    ~FormChangePassword();

    void setUsername(QString user);

signals:
    void cancelClicked();
    void selectClicked();

private slots:
    void on_cancel_clicked();
    void on_submit_clicked();

private:
    Ui::FormChangePassword *ui;
    ControllerModelInterface *interface;
    QString username;

};

#endif // FORMCHANGEPASSWORD_H
