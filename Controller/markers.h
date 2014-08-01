#ifndef MARKERS_H
#define MARKERS_H

#include "formcreateactivitywizard.h"
#include "controllermodelinterface.h"
#include "Model/modeldatainterface.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class markers;
}

class markers : public QDialog
{
    Q_OBJECT

public:
    explicit markers(QWidget *parent = 0);
    ~markers();
    void displayRubric();
    void StudentSubmissionList();
    void displayInstructorSolution();
    void setActivityID(QString aID, QString courseID);
    QString activityID;

private slots:
    void on_pushButton_GradeEssayActivity_clicked();

    void on_tableView_StudentSelection_doubleClicked(const QModelIndex &index);

    void on_pushButton_OpenInstructorSolution_clicked();

private:
    Ui::markers *ui;
    QString markerEmployeeID;
    QString selectedCourseID;
    ControllerModelInterface *interface;
    ModelDataInterface *modeldatainterface;
    QSqlQueryModel *querymodel;
    QSqlQueryModel *rubrictable;
    QSqlQueryModel *studentmodel;
    FormCreateActivityWizard *formCreateActivityWizard;
};

#endif // MARKERS_H
