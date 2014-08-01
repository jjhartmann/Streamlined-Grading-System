#ifndef CONTROLLERFORACTIVITYWIZARD_H
#include "controllermodelinterface.h"
#include "formcreateactivitywizard.h"
#include "Model/qdatamodel.h"
#include "formcreateactivitywizardcodingtests.h"
#include "Model/instructormodel.h"
#define CONTROLLERFORACTIVITYWIZARD_H

#include <QVector>
#include <QObject>

class ControllerForActivityWizard : public QObject
{
    Q_OBJECT
public:
    explicit ControllerForActivityWizard(QString activityType, QString username, QString CourseID, QObject *parent = 0);
    ~ControllerForActivityWizard();
    void initFormWizard(int activityIndex, int createModifySelect);

private slots:
    void slot_pushbutton_nextCreateGeneralActivty(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID);
    void slot_pushbutton_cancelClick();
    void slot_pushbutton_confirmClick();
    void slot_pushbutton_codingTestAdd();
    void slot_pushbutton_codingTestDel();
    //RUBRIC CONFIRM
    void slot_rubric_confirmClick(QStandardItemModel *rubricModel, QString activityID);

    //ESSAY CONFIRM
    void slot_essay_confrimClick(QString solutionPath, QString SubmissionPath, QStandardItemModel *essayFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);

    //PROBLEM SET CONFIRM
    void slot_problemSet_confirmClick(QString solutionPath, QString SubmissionPath, QStandardItemModel *problemsetFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);

    //MULTIPLE CHOICE CONFIRM
    void slot_multipleChoice_confirmClick(QString outputPath, QStandardItemModel *mcAnswerKey, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);

    //CODING CONFRIM
    void slot_coding_confirmClick(QString codingEnviroment, QStandardItemModel *codingTests, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);

    //Coding Test Pages
    void slot_pushbutton_codingTestConfirm(QStandardItemModel *generalItems, QStandardItemModel *solutionFiles, QStandardItemModel *submissionFiles, QStandardItemModel *outputFiles);
    void slot_pushbutton_codingTestCancel();


private:
    //Vars:
    QString globalActivityType;
    QString instructorUsername;
    QString globalCourseID;
    int globalModifyCreateSelect;

    //OBEJECTS
    FormCreateActivityWizard *activityWizard;
    FormCreateActivityWizardCodingTests *codingTestWizard;
    ControllerModelInterface *interface;


    // CONTAINERS CREATE
    QDataModel *essayProbsFileTypesNames;
    QDataModel *bonusMarks;
    QDataModel *latePenalty;
    QDataModel *multipleChoiceAnswerKey;
    QDataModel *codingTest;

    QVector<QStandardItemModel*> *vector_codingTest;
    QVector<QStandardItemModel*> *vector_generalItems;
    QVector<QStandardItemModel*> *vector_solutionFiles;
    QVector<QStandardItemModel*> *vector_submissionFiles;
    QVector<QStandardItemModel*> *vector_outputFiles;

    // CONTAINERS MODIFY
    QSqlQueryModel *mActivity;
    QSqlQueryModel *mRubric;
    QSqlQueryModel *mLatePenalty;
    QSqlQueryModel *mEarlyBonus;
    //EssatProb
    QSqlQueryModel *mActivityEssayProblem;
    QSqlQueryModel *mEssayProbFile;
    //MC
    QSqlQueryModel *mActivityMC;
    QSqlQueryModel *mAnswerKey;
    //Code
    QSqlQueryModel *mActivityCoding;
    QSqlQueryModel *mCodingTest;


    //FUNCTIONS
    QString fileDialogFolder();
     void deleteActivityWizard();
};

#endif // CONTROLLERFORACTIVITYWIZARD_H
