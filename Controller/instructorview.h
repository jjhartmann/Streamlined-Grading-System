#ifndef INSTRUCTORVIEW_H
#include "formcreateactivityselection.h"
#include "controllerforactivitywizard.h"
#include "Controller/controllermodelinterface.h"
#include "markers.h"
#define INSTRUCTORVIEW_H

#include <QMainWindow>



namespace Ui {
class InstructorView;
}

class InstructorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit InstructorView(QWidget *parent = 0);
    ~InstructorView();
    void initInstructorView(QString usename, QString eID);
    void refreshTableView();

signals:
    void signal_instructorLogOff();

private slots:

    //SLOTS FOR formCreateActivity
    void slot_pushbutton_cancelClick();
    void slot_pushbutton_createProblemSet();
    void slot_pushbutton_createEssay();
    void slot_pushbutton_createMultipleChoice();
    void slot_pushbutton_createCodingAssignment();

    //GUI
    void on_tableView_CourseSelection_clicked(const QModelIndex &index);
    void on_tableView_Activities_doubleClicked(const QModelIndex &index);
    void on_pushButton_createActivity_clicked();


    void on_comboBox_contextMenu_activated(int index);

    void on_actionLogOut_triggered();

    void on_comboBox_contextMenu_currentIndexChanged(int index);

    void on_tableView_Activities_clicked(const QModelIndex &index);

    void on_pushButton_markSubmission_clicked();

private:
    //Vars
    QString globalCourseID;
    QString instructorUsername;
    QString instructorEmployeeID;
    QString globalActivityID;
    QSqlQueryModel *courseModel;
    QSqlQueryModel *activiesModel;
    ControllerForActivityWizard *controlWizard;
    markers *Markers;

    Ui::InstructorView *ui;

    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;
    FormCreateActivity *formCreateActivity;

    //FUNCTIONS
    void deleteFormCreateActivity();
    void initializeWizard(QString activityName, int actIndex, int createModifySelect);
    int getActivityTypeIndex();
};

#endif // INSTRUCTORVIEW_H
