#include "Controller/controllerforactivitywizard.h"

ControllerForActivityWizard::ControllerForActivityWizard(QString activityType, QString username, QString CourseID, QObject *parent) :
    QObject(parent)
{
    interface = new ControllerModelInterface();
    globalActivityType = activityType;
    instructorUsername = username;
    globalCourseID = CourseID;

    //INIT QVECTOR
    vector_generalItems = new QVector<QStandardItemModel*>();
    vector_solutionFiles = new QVector<QStandardItemModel*>();
    vector_outputFiles = new QVector<QStandardItemModel*>();
    vector_submissionFiles = new QVector<QStandardItemModel*>();
}

ControllerForActivityWizard::~ControllerForActivityWizard(){
    delete interface;

    //Set Vectors to null
    vector_generalItems = NULL;
    vector_solutionFiles = NULL;
    vector_outputFiles = NULL;
    vector_submissionFiles = NULL;
}

void ControllerForActivityWizard::initFormWizard(int activityIndex, int createModifySelect)
{
    activityWizard = new FormCreateActivityWizard(globalActivityType, instructorUsername, globalCourseID, activityIndex);
    connect(activityWizard, SIGNAL(signal_pushbutton_cancelClick()), this, SLOT(slot_pushbutton_cancelClick()));
    connect(activityWizard, SIGNAL(signal_pushbutton_nextCreateGeneralActivity(QString,QString,QString,QString,QString,QString)), this,
            SLOT(slot_pushbutton_nextCreateGeneralActivty(QString,QString,QString,QString,QString,QString)));
    connect(activityWizard, SIGNAL(signal_pushbutton_codingTestADD()), this,SLOT(slot_pushbutton_codingTestAdd()));
    connect(activityWizard, SIGNAL(signal_pushbutton_codingTestDel()), this, SLOT(slot_pushbutton_codingTestDel()));

    //CONFIRM CLICK
    connect(activityWizard, SIGNAL(signal_pushbutton_confrimClick()), this, SLOT(slot_pushbutton_confirmClick()));
    connect(activityWizard, SIGNAL(signal_essay_confirm(QString,QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)), this, SLOT(slot_essay_confrimClick(QString,QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)));
    connect(activityWizard, SIGNAL(signal_problemset_confirm(QString,QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)), this, SLOT(slot_problemSet_confirmClick(QString,QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)));
    connect(activityWizard, SIGNAL(signal_mc_confirm(QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)), this, SLOT(slot_multipleChoice_confirmClick(QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)));
    connect(activityWizard, SIGNAL(signal_coding_confirm(QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)), this, SLOT(slot_coding_confirmClick(QString,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QString)));
    connect(activityWizard, SIGNAL(signal_rubric_additems(QStandardItemModel*,QString)), this, SLOT(slot_rubric_confirmClick(QStandardItemModel*,QString)));

    // CREATE OR MODIFY
    globalModifyCreateSelect = createModifySelect;



    if(createModifySelect == 1){
        mActivity = new QSqlQueryModel();
        mRubric = new QSqlQueryModel();
        mLatePenalty = new QSqlQueryModel();
        mEarlyBonus = new QSqlQueryModel();

        switch (activityIndex) {
        case 1: //Essay
            mActivityEssayProblem = new QSqlQueryModel();
            mEssayProbFile = new QSqlQueryModel();
            break;
        case 2: // ProblemSet
            mActivityEssayProblem = new QSqlQueryModel();
            mEssayProbFile = new QSqlQueryModel();
            break;
        case 3: //MC
            mActivityMC = new QSqlQueryModel();
            mAnswerKey = new QSqlQueryModel();
            break;
        case 4: //Coding
            mActivityCoding = new QSqlQueryModel();
            mCodingTest = new QSqlQueryModel();
            break;
        }

    }

    activityWizard->initGUI();
    activityWizard->show();
}

//ADD GENERAL ACTIVTY FRAMEWORK AND RETURN ID
void ControllerForActivityWizard::slot_pushbutton_nextCreateGeneralActivty(
        QString ActType,
        QString actName,
        QString actDescription,
        QString actLanguage,
        QString actDueDate,
        QString courseID)
{
    QString activityID = interface->insertActivitygetID(ActType, actName, actDescription, actLanguage, actDueDate, courseID);
    activityWizard->setGlobalActivtyID(activityID);
}


// PRIVATE SLOTS FROM WIZARD
void ControllerForActivityWizard::slot_pushbutton_cancelClick()
{
  deleteActivityWizard();
}

//***********************************************************
//MAIN WIZARD CONFIRM CLICKED
void ControllerForActivityWizard::slot_pushbutton_confirmClick()
{

}

void ControllerForActivityWizard::slot_rubric_confirmClick(QStandardItemModel *rubricModel, QString activityID)
{
    InstructorModel instructorModel;
    instructorModel.createRubricItems(rubricModel, activityID);
}

void ControllerForActivityWizard::slot_essay_confrimClick(QString solutionPath, QString submissionPath, QStandardItemModel *essayFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID)
{
    InstructorModel instructorModel;
    instructorModel.createEssayActvity(solutionPath, submissionPath, essayFilenames, bonusMarks, latePenalty, actvitiyID);
    deleteActivityWizard();
}

void ControllerForActivityWizard::slot_problemSet_confirmClick(QString solutionPath, QString SubmissionPath, QStandardItemModel *problemsetFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID)
{
    InstructorModel instructorModel;
    instructorModel.createProblemSetActivity(solutionPath, SubmissionPath, problemsetFilenames, bonusMarks, latePenalty, actvitiyID);
    deleteActivityWizard();
}

void ControllerForActivityWizard::slot_multipleChoice_confirmClick(QString outputPath, QStandardItemModel *mcAnswerKey, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID)
{
    InstructorModel instructorModel;
    instructorModel.createMultipleChoiceActivity(outputPath, mcAnswerKey, bonusMarks, latePenalty, actvitiyID);
    deleteActivityWizard();
}

void ControllerForActivityWizard::slot_coding_confirmClick(QString codingEnviroment, QStandardItemModel *codingTests,  QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID)
{
     InstructorModel instructorModel;
     instructorModel.createCodingAssignemtnActivity(codingEnviroment, vector_generalItems, vector_solutionFiles, vector_outputFiles, vector_submissionFiles,  bonusMarks, latePenalty, actvitiyID);
     deleteActivityWizard();
}




//CODING TEST WIZARD
void ControllerForActivityWizard::slot_pushbutton_codingTestAdd()
{
    codingTestWizard = new FormCreateActivityWizardCodingTests();
    connect(codingTestWizard, SIGNAL(signal_pusbutton_confirmClick(QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*)),
            this, SLOT(slot_pushbutton_codingTestConfirm(QStandardItemModel*,QStandardItemModel*,QStandardItemModel*,QStandardItemModel*)));
    connect(codingTestWizard, SIGNAL(signal_pushbutton_cancelClick()), this, SLOT(slot_pushbutton_codingTestCancel()));
    codingTestWizard->show();
}

void ControllerForActivityWizard::slot_pushbutton_codingTestDel()
{

}


void ControllerForActivityWizard::slot_pushbutton_codingTestConfirm(QStandardItemModel *generalItems, QStandardItemModel *solutionFiles, QStandardItemModel *submissionFiles, QStandardItemModel *outputFiles)
{
    activityWizard->setCodingTestRow(generalItems);

    vector_generalItems->push_back(generalItems);
    vector_solutionFiles->push_back(solutionFiles);
    vector_outputFiles->push_back(outputFiles);
    vector_submissionFiles->push_back(submissionFiles);

    codingTestWizard->close();
    if(codingTestWizard != NULL){
       codingTestWizard->deleteLater();
    }

}

void ControllerForActivityWizard::slot_pushbutton_codingTestCancel()
{
    codingTestWizard->close();
    if(codingTestWizard != NULL){
       codingTestWizard->deleteLater();
    }

//    activityWizard->delete_codingAssignmentTest_onCancel();

}




//PRIVATE FUNCTIONS
void ControllerForActivityWizard::deleteActivityWizard(){
    activityWizard->close();
    if(activityWizard != NULL){
       activityWizard->deleteLater();
    }
}

QString ControllerForActivityWizard::fileDialogFolder()
{
    QString fileName;
    //    fileName = QFileDialog::getExistingDirectory(this, "Open Image", "/home/jana", QFileDialog::ShowDirsOnly);
    return fileName;
}
