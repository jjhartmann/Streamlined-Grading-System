#ifndef FORMMANAGETA_H
#include "Controller/controllermodelinterface.h"
#define FORMMANAGETA_H

#include <QWidget>

namespace Ui {
class FormManageTA;
}

class FormManageTA : public QWidget
{
    Q_OBJECT

public:
    explicit FormManageTA(QWidget *parent = 0);
    ~FormManageTA();

    void initTAListGui(QString courseID, QString courseName);

signals:
    void signalManageTA_add(QString employeeID);
    void signalManageTA_delete(QString courseID, QString employeeID);
    void signalManageTA_goBack();

private slots:
    void on_pushButton_addTA_clicked();

    void on_pushButton_deleteTA_clicked();

    void on_pushButton_goBack_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    // Vars
    QString selectedCourseID;
    QString selectedCourseName;

    Ui::FormManageTA *ui;

    ControllerModelInterface *interface;
    QSqlQueryModel *listModel;

    // Functions
    void refreshList();
};

#endif // FORMMANAGETA_H
