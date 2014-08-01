#include "Model/instructormodel.h"

InstructorModel::InstructorModel()
{
}


void InstructorModel::createEssayActvity(QString solutionPath, QString SubmissionPath, QStandardItemModel *essayFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID)
{
    ModelDataInterface dataInterface("insertEssayActivity");
    int numberofFiles = essayFilenames->rowCount();

    dataInterface.insertActivityEssayProblem(activityID, QString::number(numberofFiles), solutionPath, SubmissionPath);

    for(int i = 0; i < numberofFiles; i++){
        QString fileName = essayFilenames->index(i, 0).data().toString();
        QString fileType = essayFilenames->index(i, 1).data().toString();
        dataInterface.insertEssayProblemFile(fileName, fileType, activityID);
    }

    //LATE AND BONUS MARKS
   createBonusandLateSection(bonusMarks, latePenalty, activityID);

}

void InstructorModel::createProblemSetActivity(QString solutionPath, QString SubmissionPath, QStandardItemModel *problemsetFilenames, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID)
{
    ModelDataInterface dataInterface("insertProblemSetActivity");
    int numberofFiles = problemsetFilenames->rowCount();

    dataInterface.insertActivityEssayProblem(activityID, QString::number(numberofFiles), solutionPath, SubmissionPath);

    for(int i = 0; i < numberofFiles; i++){
        QString fileName = problemsetFilenames->index(i, 0).data().toString();
        QString fileType = problemsetFilenames->index(i, 1).data().toString();
        dataInterface.insertEssayProblemFile(fileName, fileType, activityID);
    }

    //LATE AND BONUS MARKS
   createBonusandLateSection(bonusMarks, latePenalty, activityID);
}

void InstructorModel::createMultipleChoiceActivity(QString outputPath, QStandardItemModel *mcAnswerKey, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID)
{
    ModelDataInterface dataInterface("insertMultipleChoiceActivity");
    int rows = mcAnswerKey->rowCount();

    dataInterface.insertActivityMultipleChoice(activityID, outputPath);

    for(int i = 0; i < rows; i++){
        QString answer = mcAnswerKey->index(i, 0).data().toString();
        QString weight = mcAnswerKey->index(i, 1).data().toString();
        dataInterface.insertAnswerKeyInstance(answer, weight, activityID);
    }

   //LATE AND BONUS MARKS
   createBonusandLateSection(bonusMarks, latePenalty, activityID);

}

void InstructorModel::createCodingAssignemtnActivity(QString codingEnviroment, QVector<QStandardItemModel*> *vector_generalItems, QVector<QStandardItemModel*> *vector_solutionFiles, QVector<QStandardItemModel*> *vector_outputFiles, QVector<QStandardItemModel*> *vector_submissionFiles, QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID)
{
    ModelDataInterface dataInterface;
    int numberofTest = vector_generalItems->size();
    dataInterface.insertActivityCoding(activityID, codingEnviroment, QString::number(numberofTest));

    for(int i = 0; i < numberofTest; i++)
    {
        int rowSol = vector_solutionFiles->at(i)->rowCount();
        int rowOut = vector_outputFiles->at(i)->rowCount();
        int rowSub = vector_submissionFiles->at(i)->rowCount();

        //General
        QString genName = vector_generalItems->at(i)->index(0, 0).data().toString();
        QString genDescp = vector_generalItems->at(i)->index(0, 1).data().toString();
        QString genInput = vector_generalItems->at(i)->index(0, 2).data().toString();
        QString genOut  = vector_generalItems->at(i)->index(0, 3).data().toString();
        QString genErr = vector_generalItems->at(i)->index(0, 4).data().toString();

        QString codeTestID = dataInterface.insertCodingTestGetID(genName, genDescp, QString::number(rowSub), QString::number(rowOut), genInput, genOut, genErr, activityID);

        //SOLTIONS
        for(int j = 0; j < rowSol; j++)
        {
            QString fileName = vector_solutionFiles->at(i)->index(j, 0).data().toString();
            QString fileType = vector_solutionFiles->at(i)->index(j, 1).data().toString();
            QString path = vector_solutionFiles->at(i)->index(j, 2).data().toString();
            dataInterface.insertTestSolutionPath(fileName, fileType, path, codeTestID);
        }


        //SUBMISSIONS
        for(int j = 0; j < rowSol; j++)
        {
            QString fileName = vector_submissionFiles->at(i)->index(j, 0).data().toString();
            QString fileType = vector_submissionFiles->at(i)->index(j, 1).data().toString();
            QString path = vector_submissionFiles->at(i)->index(j, 2).data().toString();
            dataInterface.insertTestInputPath(fileName, fileType, path, codeTestID);
        }

        //OUTPUT
        for(int j = 0; j < rowSol; j++)
        {
            QString fileName = vector_outputFiles->at(i)->index(j, 0).data().toString();
            QString fileType = vector_outputFiles->at(i)->index(j, 1).data().toString();
            QString path = vector_outputFiles->at(i)->index(j, 2).data().toString();
            dataInterface.insertTestSampleOutputFile(fileName, fileType, path, codeTestID);
        }

    }

    createBonusandLateSection(bonusMarks, latePenalty, activityID);


}


void InstructorModel::createRubricItems(QStandardItemModel *rubricModel, QString activityID)
{
    ModelDataInterface dataInterface("RubricConections");
    int row = rubricModel->rowCount();
    for(int i = 0; i < row; i++)
    {
        QString name = rubricModel->index(i, 0).data().toString();
        QString descript = rubricModel->index(i, 1).data().toString();
        QString weight = rubricModel->index(i, 2).data().toString();
        QString points = rubricModel->index(i, 3).data().toString();
        dataInterface.insertRubric(points, name, descript, weight, activityID);
    }
}

//***********************************************************
// DELETE ACTVIITY
void InstructorModel::deleteActivity(QString actvitiyID)
{
    ModelDataInterface dataInterface;
    dataInterface.deleteActivity(actvitiyID);
}


//**************************************************************
//PRIVATE

//BONUS AND LATE PENALTY
void InstructorModel::createBonusandLateSection(QStandardItemModel *bonusMarks, QStandardItemModel *latePenalty, QString activityID)
{
    ModelDataInterface dataInterface;
    int countBonusMarks = bonusMarks->rowCount();
    int countLatePenalty = latePenalty->rowCount();

    for(int i = 0; i < countBonusMarks; i++){
        QString daysBefore = bonusMarks->index(i, 0).data().toString();
        QString percent = bonusMarks->index(i, 1).data().toString();
        dataInterface.insertActivityEarlyBonus(daysBefore, percent, activityID);
    }

    for(int i = 0; i < countLatePenalty; i++){
        QString daysAfter = latePenalty->index(i, 0).data().toString();
        QString percent = latePenalty->index(i, 1).data().toString();
        dataInterface.insertActivityLatePenalty(daysAfter, percent, activityID);
    }
}
