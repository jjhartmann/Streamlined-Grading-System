#include "Controller/viewcontroller.h"

ViewController::ViewController(QObject *parent) :
    QObject(parent)
{
}

ViewController::~ViewController()
{

}

//*********************************
// WINDOW INITIALIZATION

void ViewController::initializeLoginView(){
    loginView = new LoginView;
    loginView->show();

    //Connect
    connect(loginView, SIGNAL(signalShowAccountAcademicAdmin(QString,QString)), this, SLOT(accountTypeAcademicAdminShow(QString,QString)));
    connect(loginView, SIGNAL(signalShowAccountAdminAssistant(QString,QString)), this, SLOT(accountTypeAdminAssistantShow(QString,QString)));
    connect(loginView, SIGNAL(signalShowAccountInstructor(QString,QString)), this, SLOT(accountTypeInstructorShow(QString,QString)));
    connect(loginView, SIGNAL(signalShowAccountSysAdmin(QString,QString)), this, SLOT(accountTypeSysAdminShow(QString,QString)));
    connect(loginView, SIGNAL(signalShowAccountTATM(QString,QString)), this, SLOT(accountTypeTATMShow(QString,QString)));
    connect(loginView, SIGNAL(signalquitLoginView()), this, SLOT(quitLoginView()));


}

void ViewController::ShowInstructorView()
{
    instructorView = new InstructorView;
    instructorView->show();
}


//***********************************
// PRIVATE SLOTS

//INSTRUCTOR
void ViewController::accountTypeInstructorShow(QString username, QString eID){
    instructorView = new InstructorView;
    connect(instructorView, SIGNAL(signal_instructorLogOff()), this, SLOT(slot_instructorLogOff()));
    instructorView->initInstructorView(username, eID);

    instructorView->show();
}

void ViewController::slot_instructorLogOff()
{
    instructorView->close();
    if(instructorView != NULL){
        instructorView->deleteLater();
    }
    //Start Login View
    initializeLoginView();
}


//TATM
void ViewController::accountTypeTATMShow(QString username, QString eID){
    markerView = new MarkerView;
    connect(markerView, SIGNAL(signal_markerLogOff()), this, SLOT(slot_taTmLogOff()));
    markerView->initMarkerView(username, eID);
    markerView->show();
}

void ViewController::slot_taTmLogOff()
{
    markerView->close();
    if(markerView != NULL){
        markerView->deleteLater();
    }
    //Start Login View
    initializeLoginView();
}


//ADMIN ASSISTANT
void ViewController::accountTypeAdminAssistantShow(QString username, QString eID){
    adminAssistentView = new AdminAssistentView;
    connect(adminAssistentView, SIGNAL(signal_adminAssistantLogOff()), this, SLOT(slot_adminAssistantLogOff()));
    adminAssistentView->initAdminAssistentGui(username, eID);
    adminAssistentView->show();

}

void ViewController::slot_adminAssistantLogOff()
{
    adminAssistentView->close();
    if(adminAssistentView != NULL){
        adminAssistentView->deleteLater();
    }
    //Start Login View
    initializeLoginView();
}
//ACADEMIC ADMIN
void ViewController::accountTypeAcademicAdminShow(QString username, QString eID){
    academicAdminView = new AcademicAdminView;
    connect(academicAdminView, SIGNAL(signal_academicAdminLogOff()), this, SLOT(slot_academicAdminLogOff()));
    academicAdminView->show();
}

void ViewController::slot_academicAdminLogOff()
{
    academicAdminView->close();
    if(academicAdminView != NULL){
        academicAdminView->deleteLater();
    }
    //Start Login View
    initializeLoginView();
}


//SYS ADMIN
void ViewController::accountTypeSysAdminShow(QString username, QString eID){
    sysAdminView = new SysAdminView;
    connect(sysAdminView, SIGNAL(signal_sysAdminLogOff()), this, SLOT(slot_sysAdminLogOff()));

    sysAdminView->initSysAdminGui(username, eID);
    sysAdminView->show();
}

void ViewController::slot_sysAdminLogOff()
{
    sysAdminView->close();
    if(sysAdminView != NULL){
       sysAdminView->deleteLater();
    }
    //Start Login View
    initializeLoginView();
}


//LOGIN VIEW
void ViewController::quitLoginView(){
    loginView->close();

    if(loginView != NULL){
        loginView->deleteLater();
    }
}


