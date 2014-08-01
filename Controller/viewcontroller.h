#ifndef VIEWCONTROLLER_H
#include "academicadminview.h"
#include "adminassistentview.h"
#include "instructorview.h"
#include "markerview.h"
#include "sysadminview.h"
#include "loginview.h"
#define VIEWCONTROLLER_H

#include <QObject>
#include <QMessageBox>


class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = 0);
    ~ViewController();

    //TESTING FUNCTIONS
    void initializeLoginView();
    void ShowAcademicAdminView();
    void ShowAdminAssistentView();
    void ShowInstructorView();
    void ShowMarkerView();
    void ShowSysAdminView();

signals:

private slots:
    //INSTRUCTOR
    void accountTypeInstructorShow(QString username, QString eID);
    void slot_instructorLogOff();
    //TATM
    void accountTypeTATMShow(QString username, QString eID);
    void slot_taTmLogOff();
    //ADMIN ASSIST
    void accountTypeAdminAssistantShow(QString username, QString eID);
    void slot_adminAssistantLogOff();
    //ACADEMIC ADMIN
    void accountTypeAcademicAdminShow(QString username, QString eID);
    void slot_academicAdminLogOff();
    //SYS ADMIN
    void accountTypeSysAdminShow(QString username, QString eID);
    void slot_sysAdminLogOff();

    void quitLoginView();

private:
    //Variables
    AcademicAdminView *academicAdminView;
    AdminAssistentView *adminAssistentView;
    InstructorView *instructorView;
    MarkerView * markerView;
    SysAdminView * sysAdminView;
    LoginView *loginView;
};

#endif // VIEWCONTROLLER_H
