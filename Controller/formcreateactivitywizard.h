//Acitivty Type Index
// 1 = ProblemSet
// 2 = Essay
// 3 = MultipleChoice
// 4 = Coding Assignment

#ifndef FORMCREATEACTIVITYWIZARD_H
#define FORMCREATEACTIVITYWIZARD_H

#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QWidget>
#include <QSql>

namespace Ui {
class FormCreateActivityWizard;
}

class FormCreateActivityWizard : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreateActivityWizard(QString actName, QString username, QString cID, int index, QWidget *parent = 0);
    ~FormCreateActivityWizard();
    void initGUI();
    void delete_codingAssignmentTest_onCancel();
    void setGlobalActivtyID(QString activityID);
    bool createGeneralActivity();
    //coding
    void setCodingTestRow(const QStandardItemModel *generalItems);
    QString getSolutionPath();

signals:
    //General
    void signal_pushbutton_nextCreateGeneralActivity(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID);
    void signal_pushbutton_cancelClick();
    void signal_pushbutton_confrimClick();
    //Essay
    void signal_essay_confirm(QString solutionPath, QString SubmissionPath, QStandardItemModel *essayFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty,  QString actvitiyID);
    //ProblemSet
    void signal_problemset_confirm(QString solutionPath, QString SubmissionPath, QStandardItemModel *problemsetFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);
    //MultipleChoice
    void signal_mc_confirm(QString outputPath, QStandardItemModel *mcAnswerKey, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);
    //CodingTest
    void signal_coding_confirm(QString codingEnviroment, QStandardItemModel *codingTests,QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString actvitiyID);
    void signal_pushbutton_codingTestADD();
    void signal_pushbutton_codingTestDel();
    //RUBRIC
    void signal_rubric_additems(QStandardItemModel *rubricModel, QString activityID);



protected slots:
    void iteratorCodingAssignment_back();

private slots:
    void on_pushButton_confirm_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_Back_clicked();
    void on_pushButton_essayprob_addFiles_clicked();
    void on_pushButton_essayprob_delfiles_clicked();
    void on_pushButton_mc_browseDir_clicked();
    void on_pushButton_mc_loadAnswerKey_clicked();
    void on_pushButton_codning_addTest_clicked();
    void on_pushButton_coding_delTest_clicked();
    void on_pushButton_essayprob_browseSubPath_clicked();
    void on_pushButton_essayprob_browseSolPath_clicked();
    void on_pushButton_earlybonus_add_clicked();
    void on_pushButton_earlybonus_del_clicked();
    void on_pushButton_latepenalty_add_clicked();
    void on_pushButton_latepenalry_del_clicked();

    void on_pushButton_rubric_add_clicked();

    void on_pushButton_rubric_delete_clicked();

private:
    Ui::FormCreateActivityWizard *ui;
    QString globalActivityID;
    int globalIterator;
    QString const instructorUsername;
    QString const courseID;
    QString const activityType;
    int const activityTypeIndex;

    // CONTAINERS
    QStandardItemModel *essayFileTypesNames;
    QStandardItemModel *problemSetFileTypesNames;
    QStandardItemModel *bonusMarks;
    QStandardItemModel *latePenalty;
    QStandardItemModel *multipleChoiceAnswerKey;
    QStandardItemModel *codingTest;
    QStandardItemModel *rubric;


    //FUNCTIONS
    void iteratorPloblemSetEssay();
    void iteratorMultipleChoice();
    void iteratorCodingAssignment();
    void iteratorPloblemSetEssay_back();
    void iteratorMultipleChoice_back();
    QString fileDialogFolder();
    void processCSVFile(QString filename);
};

#endif // FORMCREATEACTIVITYWIZARD_H
