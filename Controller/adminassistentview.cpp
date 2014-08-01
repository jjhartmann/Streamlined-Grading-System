/* Contains all functions for the main UI and related actions for Administrative Assistant window */

#include "Controller/adminassistentview.h"
#include "ui_adminassistentview.h"

#include <QMessageBox>


AdminAssistentView::AdminAssistentView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminAssistentView)
{
    ui->setupUi(this);

    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface;
    this->setWindowTitle("Administrative Assistant Main Window");
    ui->tableView_Course->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->label_courseInstructorName->setText("");
}

AdminAssistentView::~AdminAssistentView()
{
    delete ui;
    delete interface;

}

// Initialize the table model in the admin assistant UI
void AdminAssistentView::initAdminAssistentGui(QString username, QString eID)
{
    // Init GUI
    adminAssistentUsername = username;
    adminAssistentEmployeeID = eID;
    ui->label_userAccountName->setText(adminAssistentUsername);
    refreshList();
}

//******************************************
// On pushButton clicked

void AdminAssistentView::on_pushButton_createCourse_clicked()
{
    createCourse = new FormCreateCourse;

    //connections
    connect(createCourse, SIGNAL(signalButtonClicked_create(QString,QString,QString,QString,QString)), this, SLOT(slotCreateCourse_create(QString,QString,QString,QString,QString)));
    connect(createCourse, SIGNAL(signalBurronClicked_cancel()), this, SLOT(slotCreateCoruse_cancel()));

    createCourse->show();

}

void AdminAssistentView::on_pushButton_deleteCourse_clicked()
{
    int row = -1;
    row = ui->tableView_Course->selectionModel()->currentIndex().row();
    if(row != -1)
    {
        QString courseID = ui->tableView_Course->model()->index(row, 0).data().toString();
        interface->adminAssistRemoveAllTATM(courseID);
        interface->adminAssistRemoveInstructor(courseID);
        interface->deleteCourse(courseID);

        ui->lineEdit_coursename->setText("");
        ui->lineEdit_coursenumber->setText("");
        refreshList();
    }
}

void AdminAssistentView::on_pushButton_modifyCourse_clicked()
{
    QString courseName = ui->lineEdit_coursename->text();
    QString courseNumber = ui->lineEdit_coursenumber->text();
    QString startDate = "'" + ui->dateEdit_startDate->text() + "'";
    QString endDate = "'" + ui->dateEdit_endDate->text() + "'";

    interface->adminAssistModifyCourse(courseID_selected, courseName, courseNumber, startDate, endDate );
    refreshList();
}

void AdminAssistentView::on_pushButton_assignInstructor_clicked()
{
    assignIntstructor = new FormAssignInstructortoCourse;
    QMessageBox msgBox;

    int row = -1;
    row = ui->tableView_Course->selectionModel()->currentIndex().row();
    if(row != -1)
    {
        //        ui->label_courseInstructorName->setText();
        //Course selection before assigning instructor
        courseID_selected = ui->tableView_Course->model()->index(row, 0).data().toString();

        //Connections
        connect(assignIntstructor, SIGNAL(signalassignButtonClicked(QString)), this, SLOT(slotAssignInsturctor_assign(QString)));
        connect(assignIntstructor, SIGNAL(signalcancelButtonClicked()), this, SLOT(slotAssignInstructor_cancel()));
        assignIntstructor->show();
    }
    else
    {
        msgBox.setText("First select a course");
        msgBox.exec();
    }

}

void AdminAssistentView::on_pushButton_assignTA_clicked()
{
    manageTA = new FormManageTA;
    QMessageBox msgBox;

    int row = -1;
    row = ui->tableView_Course->selectionModel()->currentIndex().row();
    if(row != -1)
    {
        courseID_selected = ui->tableView_Course->model()->index(row, 0).data().toString();
        courseName_selected = ui->tableView_Course->model()->index(row, 1).data().toString();
        //Connections
        connect(manageTA, SIGNAL(signalManageTA_add(QString)), this, SLOT(slotManageTA_add(QString)));
        connect(manageTA, SIGNAL(signalManageTA_delete(QString, QString)), this, SLOT(slotManageTA_delete(QString, QString)));
        connect(manageTA, SIGNAL(signalManageTA_goBack()), this, SLOT(slotManageTA_goBack()));
        manageTA->initTAListGui(courseID_selected, courseName_selected);
        manageTA->show();
    }
    else
    {
        msgBox.setText("First select a course");
        msgBox.exec();
    }
}

void AdminAssistentView::on_pushButton_importStudentList_clicked()
{
    studentList = new FormAssignStudentList;
    QMessageBox msgBox;

    int row = -1;
    row = ui->tableView_Course->selectionModel()->currentIndex().row();
    if(row != -1)
    {
        courseID_selected = ui->tableView_Course->model()->index(row, 0).data().toString();
        studentList->initStudentForm(courseID_selected);
        //Connections
        connect(studentList, SIGNAL(signalStudentList_confirm(QVector<QString>)), this, SLOT(slotStudentList_confirm(QVector<QString>)));
        connect(studentList, SIGNAL(signalStudentList_goback()), this, SLOT(slotSutdentList_goback()));

        studentList->show();
    }
    else
    {
        msgBox.setText("First select a course");
        msgBox.exec();
    }

}

//end of pushButtons

//**********************************************************************
//Custom Slots

//INSTRUCTOR
void AdminAssistentView::slotAssignInsturctor_assign(QString instructorEID){
    //Database logic
    interface->adminAssistRemoveInstructor(courseID_selected);
    interface->adminAssistAssignInstructor(courseID_selected, instructorEID);
    if(assignIntstructor == NULL){
        assignIntstructor->deleteLater();
    }
}

void AdminAssistentView::slotAssignInstructor_cancel(){
    if(assignIntstructor == NULL){
        assignIntstructor->deleteLater();
    }
}

//COURSE
void AdminAssistentView::slotCreateCourse_create(QString courseName, QString courseNumber, QString startDate, QString endDate, QString instructorEID)
{
    //Datebase stuff
    QString courseID = interface->adminAssistCreateCourse(courseName, courseNumber, startDate, endDate, instructorEID);
    if(instructorEID != 0)
    {
        interface->adminAssistAssignInstructor(courseID, instructorEID);
    }
    // Hide create form when not in use
    if(createCourse == NULL){
        delete createCourse;
        createCourse = 0;
    }
    refreshList();
}

void AdminAssistentView::slotCreateCoruse_cancel(){
    if(createCourse == NULL){
        delete createCourse;
        createCourse = 0;
    }
}

//MANAGE TA
void AdminAssistentView::slotManageTA_add(QString employeeID){
    //Database Stuff
    interface->adminAssistAssignTATM(courseID_selected, employeeID);
    if(manageTA == NULL){
        manageTA->deleteLater();
    }
}

void AdminAssistentView::slotManageTA_delete(QString courseID, QString employeeID){
    //Database  Stuff
    interface->adminAssistRemoveTATM(courseID, employeeID);
}

void AdminAssistentView::slotManageTA_goBack(){
    manageTA->close();
    if(manageTA != NULL){
        manageTA->deleteLater();
    }
}

//STUDENT LIST
void AdminAssistentView::slotStudentList_confirm(QVector<QString> vector){
    //Database stuff

    if(studentList != NULL){
        studentList->deleteLater();
    }
}

void AdminAssistentView::slotSutdentList_goback(){
    if(studentList != NULL){
        studentList->deleteLater();
    }
}

// end custom slots
//***************************************************************



// log off signal when button clicked
void AdminAssistentView::on_actionLogOut_triggered()
{
    emit signal_adminAssistantLogOff();
}

// Show/refresh table model
void AdminAssistentView::refreshList()
{
    courseModel = interface->getCourseList();
    ui->tableView_Course->setModel(courseModel);
}

// copy course information into lineEdit for modification
void AdminAssistentView::on_tableView_Course_doubleClicked(const QModelIndex &index)
{
    courseID_selected = ui->tableView_Course->model()->index(index.row(),0).data().toString();

    ui->lineEdit_coursename->setText(ui->tableView_Course->model()->index(index.row(),1).data().toString());
    ui->lineEdit_coursenumber->setText(ui->tableView_Course->model()->index(index.row(),2).data().toString());
    ui->dateEdit_startDate->setDate(ui->tableView_Course->model()->index(index.row(),3).data().toDate());
    ui->dateEdit_endDate->setDate(ui->tableView_Course->model()->index(index.row(),4).data().toDate());


}
