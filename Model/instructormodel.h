#ifndef INSTRUCTORMODEL_H
#include "modeldatainterface.h"
#define INSTRUCTORMODEL_H

#include <QStandardItemModel>
#include <QVector>
#include <QString>


class InstructorModel
{
public:
    InstructorModel();

    void createEssayActvity(QString solutionPath, QString SubmissionPath, QStandardItemModel *essayFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID);
    void createProblemSetActivity(QString solutionPath, QString SubmissionPath, QStandardItemModel *problemsetFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID);
    void createMultipleChoiceActivity(QString outputPath, QStandardItemModel *mcAnswerKey, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID);
    void createCodingAssignemtnActivity(QString codingEnviroment, QVector<QStandardItemModel *> *vector_generalItems, QVector<QStandardItemModel *> *vector_solutionFiles, QVector<QStandardItemModel *> *vector_outputFiles, QVector<QStandardItemModel *> *vector_submissionFiles, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID);
    void createRubricItems(QStandardItemModel *rubricModel, QString activityID);
    void deleteActivity(QString actvitiyID);
private:
    void createBonusandLateSection(QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID);
};

#endif // INSTRUCTORMODEL_H
