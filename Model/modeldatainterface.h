#ifndef MODELDATAINTERFACE_H
#define MODELDATAINTERFACE_H
#include <QString>
#include <QtSql>

using namespace std;

class ModelDataInterface
{
public:
    ModelDataInterface();
    ModelDataInterface(QString connectionName);
    ~ModelDataInterface();

    // ******************************************
    // INSERT FUNCTIONS
    // Account
    bool checkStudent(QString StudentID);
    bool insertAccount(QString employeeID, QString username, QString password, QString firstName, QString surName, QString accountType);
    bool insertAccount(QString employeeID, QString username, QString password, QString firstName, QString surName);
    bool addAccountTypeInstructor(QString employeeID);
    bool addAccountTypeTATM(QString employeeID);
    bool addAccountTypeAdminAssistent(QString employeeID);
    bool addAccountTypeAcademicAdmin(QString employeeID);
    bool addAccountTypeSysAdmin(QString employeeID);
    //Students
    bool insertStudent(QString studentID, QString FName, QString SurName);
    bool insertStudentCourse(QString courseID, QString studentID);
    bool insertStudentRubricGrade(QString courseID, QString studentID);
    bool insertStudentActivityGrade(QString courseID, QString studentID);
    //Course
    QString insertCourseGetID(QString courseName, QString courseNumber, QString startDate, QString endDate);
    bool assigningTAtoCourse(QString employeeID, QString CourseID);
    bool assigningInstructortoCourse(QString employeeID, QString CourseID);
    //Grades
    bool insertCourseGrade(QString courseID, QString studentID, QString courseGrade);
    bool insertRubricGrade(QString rubricID, QString studentID, QString rubricGradeInstance);
    bool insertActivityGrade(QString activityID, QString studentID, QString activityGrade);
    // Acctivity General
    QString insertActivitygetID(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID);
    bool insertActivity(QString activityType, QString name, QString language, QString courseID);
    bool insertActivity(QString activityType, QString name, QString description, QString language, QString dueDate, QString courseID);
    bool insertActivityLatePenalty(QString dayspast, QString percentage, QString activityID);
    bool insertActivityEarlyBonus(QString dayspast, QString percentage, QString activityID);
    bool insertRubric(QString number, QString name, QString description, QString weight, QString activityID);
    //Essay Problem Set
    bool insertActivityEssayProblem(QString activityID, QString numberofFiles, QString solutionPath, QString submissionPath);
    bool insertEssayProblemFile(QString fileName, QString fileType, QString activityID);
    //MC
    bool insertActivityMultipleChoice(QString activityID, QString resultsPath);
    bool insertAnswerKeyInstance(QString answer, QString weight, QString activityID);
    //Coding
    bool insertActivityCoding(QString activityID, QString enviroment, QString mTests);
    QString insertCodingTestGetID(QString name, QString description, QString numberofInputFiles, QString numberofOutputFiles, QString consoleInputFilePath, QString consoleOuputPath, QString consoleErrorFilePath, QString activityID);
    bool insertCodingTest(QString name, QString description, QString numberofInputFiles, QString numberofOutputFiles, QString consoleInputFilePath, QString consoleOuputPath, QString consoleErrorFilePath, QString activityID);
    bool insertTestInputPath(QString fileName, QString fileType, QString inputPath, QString codeTestID);
    bool insertTestSolutionPath(QString fileName, QString fileType, QString solutionPath, QString codeTestID);
    bool insertTestSampleOutputFile(QString fileName, QString fileType, QString outputPath, QString codeTestID);

    //********************************************
    // SELECT FUNCTIONS (GET)
    QString getAccountPassword(QString username);
    QString getDatabaseInstance(QString dataTable, QString lookupAttribute, QString desiredAttribute, QString lookupValue);
    QSqlQueryModel *getAllRubricwithActivityID(QString ActivityID);
    QSqlQueryModel *getInstructorSolutionPath(QString ActTypeID);
    QSqlQueryModel *getEssayProblemFileName(QString ActTypeID);
    QSqlQueryModel *getActivityEssayProblemSubmissionPath(QString ActTypeID);
    QString getCourseIDfromCourse(QString courseName, QString courseNumber, QString startDate);
    QSqlQueryModel *getAllTaTmAccounts();
    QSqlQueryModel* getAllUsers(); //Edit
    QSqlQueryModel* getAllCourses(); //Edit
    QVector<QString>* getUserAccountTypes(QString userName);
    QSqlQueryModel *getAllvarTablewithCondition(QString tableName, QString lookupAttribute, QString lookupValue);
    QSqlQueryModel *getAllInstructorAccounts();
    QSqlQueryModel *getAllvarTable(QString tableName);
    QSqlQueryModel *getAllCoursesForInstructor(QString employeeID);

    bool checkIfCoursehasInstructor(QString courseID);
    QSqlQueryModel *getStudentsFromCourse(QString CourseID);



    //********************************************
    // UPDATE FUNCTIONS
    bool updateAccountPasswordFlag(QString username, int flagValue);
    bool updateAccountPassword(QString employeeID, QString password);
    bool updateDatabaseInstance(QString dataTable, QString setAttribute, QString lookupAttribute, QString lookupValue, QString setValue);
    bool updateAccountAllAttributes(QString employeeID, QString username, QString firstname, QString lastname);
    bool updateCourseAltributes(QString courseID, QString courseName, QString courseNumber, QString startDate, QString endDate);

    //********************************************
    // DELETE FUNCTIONS
    bool deleteAccount(QString employeeID);
    bool deleteAccountRoleInstructor(QString employeeID);
    bool deleteAccountRoleTATM(QString employeeID);
    bool deleteAccountRoleAdminAssist(QString employeeID);
    bool deleteAccountRoleSysAdmin(QString employeeID);
    bool deleteAccountRoleAcademic(QString employeeID);

    bool deleteCourse(QString courseID);
    bool deleteInstructorFromCourse(QString courseID);
    bool deleteAllTATMFromCourse(QString courseID);
    bool deleteTATMFromCourse(QString courseID, QString employeeID);

    bool deleteActivity(QString activityID);



private:
    QString connectionTemplate;
    QString connectionString;
    QSqlDatabase db;

    //FUNCTIONS
    bool insertQuerytoDatabase(QString query);
    void checkForErrors(QSqlQuery *query, int fieldInt);
    void checkForErrors(QSqlQueryModel *model);
    void checkForErrors(QSqlQuery *query);

};

#endif // MODELDATAINTERFACE_H
