#ifndef ADMINASSISTENTVIEW_H
#include "formassigninstructortocourse.h"
#include "formcreatecourse.h"
#include "formmanageta.h"
#include "formassignstudentlist.h"
#define ADMINASSISTENTVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Controller/controllermodelinterface.h"


namespace Ui {
class AdminAssistentView;
}

class AdminAssistentView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminAssistentView(QWidget *parent = 0);
    ~AdminAssistentView();

    void initAdminAssistentGui(QString username, QString eID);
    void setCourseID(QString courseID);
    QString CourseID;
signals:
    void signal_adminAssistantLogOff();

private slots:
    void on_pushButton_createCourse_clicked();
    void on_pushButton_deleteCourse_clicked();
    void on_pushButton_modifyCourse_clicked();

    void on_pushButton_assignInstructor_clicked();
    void on_pushButton_assignTA_clicked();

    void on_pushButton_importStudentList_clicked();

    void on_actionLogOut_triggered();

    //Custom Slots
    void slotAssignInsturctor_assign(QString instructorEID);
    void slotAssignInstructor_cancel();

    void slotCreateCourse_create(QString courseName, QString courseNumber, QString startDate, QString endDate, QString instructorEID);
    void slotCreateCoruse_cancel();

    void slotManageTA_add(QString employeeID);
    void slotManageTA_delete(QString courseID, QString employeeID);
    void slotManageTA_goBack();

    void slotStudentList_confirm(QVector<QString> vector);
    void slotSutdentList_goback();

    // end

    void on_tableView_Course_doubleClicked(const QModelIndex &index);


private:
    // Vars
    QString adminAssistentUsername;
    QString adminAssistentEmployeeID;
    QString courseID_selected;
    QString courseName_selected;


    // Functions
    Ui::AdminAssistentView *ui;

    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;
    FormAssignInstructortoCourse *assignIntstructor;
    FormCreateCourse *createCourse;
    FormManageTA *manageTA;
    FormAssignStudentList *studentList;
    QSqlQueryModel *courseModel;
    void refreshList();

};

#endif // ADMINASSISTENTVIEW_H
