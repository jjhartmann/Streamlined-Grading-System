/* Contain functions for the main window UI of instructor accounts */

#include "Controller/instructorview.h"
#include "ui_instructorview.h"



InstructorView::InstructorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstructorView)
{
    ui->setupUi(this);

    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface;
    this->setWindowTitle("Instructor Main Window");
    ui->tableView_CourseSelection->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Activities->setSelectionBehavior(QAbstractItemView::SelectRows);

    //ControllerWizard

}

InstructorView::~InstructorView()
{
    delete ui;
    delete interface;

//    if(courseModel != NULL){
//        courseModel->clear();
//       courseModel->deleteLater();
//    }
//    if(activiesModel != NULL){
//       activiesModel->clear();
//       activiesModel->deleteLater();
//    }

}

void InstructorView::initInstructorView(QString username, QString eID){
    instructorUsername = username;
    instructorEmployeeID = eID;

    ui->label_userAccountName->setText(username);
    refreshTableView();
}

//GUI SLOTS
void InstructorView::on_tableView_CourseSelection_clicked(const QModelIndex &index)
{
    globalCourseID = ui->tableView_CourseSelection->model()->index(index.row(), 0).data().toString();
    activiesModel = interface->getAllActivitiesInstructor(globalCourseID);
    ui->tableView_Activities->setModel(activiesModel);
    ui->tableView_CourseSelection->horizontalHeader()->setStretchLastSection(true);
}


void InstructorView::on_tableView_Activities_doubleClicked(const QModelIndex &index)
{

}

void InstructorView::on_comboBox_contextMenu_activated(int index)
{

}

void InstructorView::on_tableView_Activities_clicked(const QModelIndex &index)
{
    globalActivityID = activiesModel->index(ui->tableView_Activities->currentIndex().row(), 0).data().toString();
}

//*************************************

void InstructorView::on_pushButton_createActivity_clicked()
{
    int row = -1;
    row = ui->tableView_CourseSelection->selectionModel()->currentIndex().row();
   if(row != -1)
   {
    formCreateActivity = new FormCreateActivity();
    //CONNECTIONS
    connect(formCreateActivity, SIGNAL(signal_formCreateActivity_CancelClicked()), this, SLOT(slot_pushbutton_cancelClick()));
    connect(formCreateActivity, SIGNAL(signal_formCreateActivity_CreateCodingAssign()), this, SLOT(slot_pushbutton_createCodingAssignment()));
    connect(formCreateActivity, SIGNAL(signal_formCreateActivity_CreateMultipleChoice()), this, SLOT(slot_pushbutton_createMultipleChoice()));
    connect(formCreateActivity, SIGNAL(signal_formCreateActivity_CreateProblemSet()), this, SLOT(slot_pushbutton_createProblemSet()));
    connect(formCreateActivity, SIGNAL(signal_formCreateActivity_CreateEssay()), this, SLOT(slot_pushbutton_createEssay()));
    formCreateActivity->initFormCreateAcitivity(instructorUsername);
    formCreateActivity->show();
   } else
   {
       QMessageBox box;
       box.setText("Please Choose a Course first.");
       box.exec();
   }
}


//**********************************************************************
//OPTIONS MENUS

void InstructorView::on_comboBox_contextMenu_currentIndexChanged(int index)
{
    int currentActIndex;
    switch (index) {
    case 1:
        //Modify
        currentActIndex = getActivityTypeIndex();
        if(currentActIndex == 1) {
            initializeWizard("Essay", 1, 1);
         }
        if(currentActIndex == 2){
            initializeWizard("Problem Set", 2, 1);
        }
        if(currentActIndex == 3){
            initializeWizard("Multiple Choice", 3, 1);
        }
        if(currentActIndex == 4){
            initializeWizard("Coding Assignment", 4, 1);
        }
         ui->comboBox_contextMenu->setCurrentIndex(0);

        break;

    case 2:
        //Delete
        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "Confirm", "Are you sure you want to delete this Activity?",
                                    QMessageBox::Yes|QMessageBox::No);
        if(box == QMessageBox::Yes)
        {
            InstructorModel inModel;
            inModel.deleteActivity(globalActivityID);
        }

        ui->comboBox_contextMenu->setCurrentIndex(0);
        refreshTableView();

        break;
    case 3:
        //Grade

        break;
    }
}



//SLOTS FOR FROM CREATE ACTIVTY
void InstructorView::slot_pushbutton_cancelClick()
{
    deleteFormCreateActivity();
}


void InstructorView::slot_pushbutton_createEssay()
{
    initializeWizard("Essay", 1, 0);
}

void InstructorView::slot_pushbutton_createProblemSet()
{
    initializeWizard("Problem Set", 2, 0);

}

void InstructorView::slot_pushbutton_createMultipleChoice()
{
    initializeWizard("Multiple Choice", 3, 0);
}

void InstructorView::slot_pushbutton_createCodingAssignment()
{
    initializeWizard("Coding Assignment", 4, 0);
}



//LOG OFF

void InstructorView::on_actionLogOut_triggered()
{
   emit signal_instructorLogOff();
}



//PRIVATE FUNCTIONS
void InstructorView::refreshTableView(){
    courseModel = interface->getAllCoursefroInstructor(instructorEmployeeID);
    ui->tableView_CourseSelection->setModel(courseModel);
    ui->tableView_CourseSelection->horizontalHeader()->setStretchLastSection(true);

    activiesModel = interface->getAllActivitiesInstructor(globalCourseID);
    ui->tableView_Activities->setModel(activiesModel);
    ui->tableView_Activities->horizontalHeader()->setStretchLastSection(true);
}


//*******************************************************************
//INITIALIZE THE WIZARD
void InstructorView::initializeWizard(QString activityName, int actIndex, int createModifySelect){
    controlWizard = new ControllerForActivityWizard(activityName, instructorUsername, globalCourseID);
    controlWizard->initFormWizard(actIndex, createModifySelect);
    //DELETE THE SELECTION FORM
    deleteFormCreateActivity();
}


void InstructorView::deleteFormCreateActivity(){
    formCreateActivity->close();
    if(formCreateActivity != NULL){
        formCreateActivity->deleteLater();
    }
}

int InstructorView::getActivityTypeIndex()
{
    int actIndex;
   QString actName = activiesModel->index(ui->tableView_Activities->currentIndex().row(), 1).data().toString();
   if(actName == "'Essay'"){
       actIndex = 1;
   }
   if (actName == "'Problem Set'"){
       actIndex = 2;
   }
   if(actName == "'Multiple Choice'"){
       actIndex = 3;
   }
   if (actName == "'Coding Assignment'"){
       actIndex = 4;
   }

}

void InstructorView::on_pushButton_markSubmission_clicked()
{
    Markers = new markers;
    Markers->setActivityID(globalActivityID, globalCourseID);
    Markers->displayRubric();
    Markers->show();
}
