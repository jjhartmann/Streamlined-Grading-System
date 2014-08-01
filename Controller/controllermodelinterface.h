#ifndef CONTROLLERMODELINTERFACE_H
#include "Model/modeldatainterface.h"
#include "Model/systemadminmodel.h"

#define CONTROLLERMODELINTERFACE_H
#include <vector>
#include <QString>


using namespace std;

class ControllerModelInterface
{
public:
    ControllerModelInterface();

    //FOR LOGIN OPERATIONS
    bool checkCredentials(QString password, QString username);
    int checkAccountType(QString username);
    bool checkMultipleAccounts(QString username);
    bool checkPasswordFlag(QString username);
    void changePassword(QString password, QString username);
    QVector<QString>* getMultipleAccounts(QString username);
    QString getemployeeID(QString username);


    //SYS ADMIN OPERATION
    void sysadminModifyAccount(QString employeeID, QString username, QString firstname, QString lastname, bool chkbxInstructor,
                               bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin,
                               bool currentchkbxInstructor, bool currentchkbxTA, bool currentchkbxAcademicAdmin, bool currentchkbxAdminAssistant, bool currentchkbxSysAdmin);

    void sysadminCreateAccount(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                               bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin);
    void deleteAccount(QString employeeID);
    QSqlQueryModel *getUserAccounts();


    //ADMIN ASSITENT OERATION
    QString adminAssistCreateCourse(QString courseName, QString courseNumber, QString startDate, QString endDate, QString instructorID);
    QString adminAssistGetInstructorName(QString courseID);

    void adminAssistModifyCourse(QString courseID, QString courseName, QString courseNumber, QString startDate, QString endDate);
    void adminAssistAssignInstructor(QString courseID, QString eID);
    void adminAssistRemoveInstructor(QString courseID);
    void adminAssistAssignTATM(QString courseID, QString eID);
    void adminAssistRemoveAllTATM(QString courseID);
    void adminAssistRemoveTATM(QString courseID, QString eID);
    void deleteCourse(QString courseID);

    bool adminAssistCheckInstructor(QString courseID);

    QSqlQueryModel *getCourseList();
    QSqlQueryModel *getTAList(QString courseID);


    //INSTRUCTOR OPERATIONS
    QSqlQueryModel *getAllCoursefroInstructor(QString employeeID);
    QSqlQueryModel *getAllActivitiesInstructor(QString courseID);
    QString getSolutionPath(QString SolutionPath);
    QString getSubmissionPath(QString SubmissionPath);
    QString getFileName(QString fileName);
    QString insertActivitygetID(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID);
    QSqlQueryModel *getAllRubricItems(QString activityID);
    QSqlQueryModel *getStudentList(QString courseID);


private:

    //Functinos
};

#endif // CONTROLLERMODELINTERFACE_H
