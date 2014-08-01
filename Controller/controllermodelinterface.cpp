#include "Controller/controllermodelinterface.h"


//*************************************************
// Public Functons

ControllerModelInterface::ControllerModelInterface()
{
}

//*****************************************
// LOGIN LOGIC
bool ControllerModelInterface::checkCredentials(QString password, QString username){
    ModelDataInterface model;
    bool match = false;
    QString realpassword = model.getAccountPassword(username);
    if(password == realpassword){
        match = true;
    }
    return match;

}

int ControllerModelInterface::checkAccountType(QString username){
    ModelDataInterface model;
    QVector<QString> *account = model.getUserAccountTypes(username);
    int intType = 0;

    QString type = account->at(0);
    if(type == "INSTRUCTOR"){
        intType = 1;
    } else if(type == "TASSISTENT"){
        intType = 2;
    } else if(type == "ASSISTENTA"){
        intType = 3;
    } else if(type == "ACEDEMICADMN"){
        intType = 4;
    } else if(type == "SYSTEMADMN"){
        intType = 5;
    }

    if(account != NULL){
        delete account;
    }

    return intType;

}

bool ControllerModelInterface::checkMultipleAccounts(QString username){
    bool multiaccount = false;

    ModelDataInterface model("connection1");
    QVector<QString> *vector = model.getUserAccountTypes(username);

    if(vector->length() > 1)
        multiaccount = true;

    if(vector != NULL){
        delete vector;
    }

    return multiaccount;
}

QVector<QString>* ControllerModelInterface::getMultipleAccounts(QString username){
    ModelDataInterface model("getMultipleAccountsConnection");
    QVector<QString> *vector = model.getUserAccountTypes(username);

    return vector;
}

bool ControllerModelInterface::checkPasswordFlag(QString username){
    bool flag = false;
    ModelDataInterface model("checkPasswordFlagConnect");
    QString dflag = model.getDatabaseInstance("Account", "UserName", "PasswordFlag", username);

    if(dflag == "1")
        flag = true;

    return flag;
}

void ControllerModelInterface::changePassword(QString password, QString username){
    ModelDataInterface model("changePasswordConnect");
    QString eID = model.getDatabaseInstance("Account", "UserName", "EmployeeID", username);
    model.updateAccountPassword(eID, password);
    model.updateAccountPasswordFlag(username, 0);

}

QString ControllerModelInterface::getemployeeID(QString username){
    ModelDataInterface dataInterface;
    return dataInterface.getDatabaseInstance("Account", "UserName", "EmployeeID", username);
}


//**********************************************************************************************
//SYSADMIN FUNCTIONS
void ControllerModelInterface::sysadminModifyAccount(QString employeeID, QString username, QString firstname, QString lastname, bool chkbxInstructor,
                                                     bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin,
                                                     bool currentchkbxInstructor, bool currentchkbxTA, bool currentchkbxAcademicAdmin, bool currentchkbxAdminAssistant, bool currentchkbxSysAdmin){
    SystemAdminModel::sysadminModifyAccount(employeeID, username, firstname, lastname, chkbxInstructor, chkbxTA, chkbxAcademicAdmin, chkbxAdminAssistant, chkbxSysAdmin, currentchkbxInstructor, currentchkbxTA, currentchkbxAcademicAdmin, currentchkbxAdminAssistant, currentchkbxSysAdmin);
}

void ControllerModelInterface::sysadminCreateAccount(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                                     bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin){
    SystemAdminModel::sysadminCreateAccount(employeeID, username, password, firstname, lastname, chkbxInstructor, chkbxTA, chkbxAcademicAdmin, chkbxAdminAssistant, chkbxSysAdmin);

}

void ControllerModelInterface::deleteAccount(QString employeeID){
    ModelDataInterface dataInterface;
    dataInterface.deleteAccount(employeeID);
}

//GET ALL USER ACCOUNTS
QSqlQueryModel *ControllerModelInterface::getUserAccounts(){
    ModelDataInterface *dataInterface = new ModelDataInterface("sysadminModelView");
    QSqlQueryModel *model = dataInterface->getAllUsers();
    if(dataInterface != NULL){

    }
    return model;

}

//**********************************************************************************************
//ADMIN ASSISTENT FUNCTIONS
QString ControllerModelInterface::adminAssistCreateCourse(QString courseName, QString courseNumber, QString startDate, QString endDate, QString instructorID)
{
    ModelDataInterface dataInterface;
    return dataInterface.insertCourseGetID(courseName, courseNumber, startDate, endDate);
}

QString ControllerModelInterface::adminAssistGetInstructorName(QString courseID)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("adminAssistGetInstructor");
    QString eID = dataInterface->getDatabaseInstance("CourseInstructor", "CourseID", "EmployeeID", courseID);
    return eID;
    //            dataInterface.getDatabaseInstance("CourseInstructor", "CourseID", "EmployeeID", courseID);

}

void ControllerModelInterface::adminAssistModifyCourse(QString courseID, QString courseName, QString courseNumber, QString startDate, QString endDate)
{
    ModelDataInterface dataInterface;
    dataInterface.updateCourseAltributes(courseID, courseName, courseNumber, startDate, endDate);
}

void ControllerModelInterface::adminAssistAssignInstructor(QString courseID, QString eID)
{
    ModelDataInterface dataInterface;
    dataInterface.assigningInstructortoCourse(eID, courseID);
}

void ControllerModelInterface::adminAssistRemoveInstructor(QString courseID)
{
    ModelDataInterface dataInterface;
    dataInterface.deleteInstructorFromCourse(courseID);
}

void ControllerModelInterface::adminAssistAssignTATM(QString courseID, QString eID)
{
    ModelDataInterface dataInterface;
    dataInterface.assigningTAtoCourse(eID, courseID);
}

void ControllerModelInterface::adminAssistRemoveAllTATM(QString courseID)
{
    ModelDataInterface dataInterface;
    dataInterface.deleteAllTATMFromCourse(courseID);
}

void ControllerModelInterface::adminAssistRemoveTATM(QString courseID, QString eID)
{
    ModelDataInterface dataInterface;
    dataInterface.deleteTATMFromCourse(courseID, eID);
}

void ControllerModelInterface::deleteCourse(QString courseID)
{
    ModelDataInterface dataInterface;
    dataInterface.deleteCourse(courseID);
}

bool ControllerModelInterface::adminAssistCheckInstructor(QString courseID)
{
    ModelDataInterface dataInterface;
    return dataInterface.checkIfCoursehasInstructor(courseID);
}

// GET ALL COURSES
QSqlQueryModel *ControllerModelInterface::getCourseList()
{
    ModelDataInterface *dataInterface = new ModelDataInterface("adminAssistModelView");
    QSqlQueryModel *model = dataInterface->getAllCourses();
    if(dataInterface != NULL){

    }
    return model;

}

// GET TA LIST
QSqlQueryModel *ControllerModelInterface::getTAList(QString courseID)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("adminAssistTAListView");
    QSqlQueryModel *model = dataInterface->getAllvarTablewithCondition("CourseTATM", "CourseID", courseID);
    if(dataInterface != NULL){

    }
    return model;
}

//**********************************************************************************************
//INSTRUCTOR FUNCTIONS

QSqlQueryModel *ControllerModelInterface::getAllCoursefroInstructor(QString employeeID){
    ModelDataInterface *dataInterface = new ModelDataInterface("instructorGetCourses");
    QSqlQueryModel *model = dataInterface->getAllCoursesForInstructor(employeeID);
    if(dataInterface != NULL){

    }
    return model;

}

QSqlQueryModel *ControllerModelInterface::getAllActivitiesInstructor(QString courseID){
    ModelDataInterface *dataInterface = new ModelDataInterface("instructorGetActivities");
    QSqlQueryModel *model = dataInterface->getAllvarTablewithCondition("Activity", "CourseID", courseID);
    if(dataInterface != NULL){

    }
    return model;

}

QString ControllerModelInterface::insertActivitygetID(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID){
    ModelDataInterface dataInterface;
    QString activityID = dataInterface.insertActivitygetID(ActType, actName, actDescription, actLanguage, actDueDate, courseID);
    return activityID;

}

QSqlQueryModel *ControllerModelInterface::getAllRubricItems(QString activityID){
    ModelDataInterface *dataInterface = new ModelDataInterface("markerGetRubric");
    QSqlQueryModel *model = dataInterface->getAllRubricwithActivityID(activityID);

    if(dataInterface != NULL){

    }
    return model;

}

QSqlQueryModel *ControllerModelInterface::getStudentList(QString courseID)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("markerGetStudent");
    QSqlQueryModel *model = dataInterface->getStudentsFromCourse(courseID);

    if(dataInterface != NULL){

    }
    return model;

}


QString ControllerModelInterface::getSolutionPath(QString SolutionPath)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("GetSolutionPath");
    QString eID = dataInterface->getDatabaseInstance("ActivityEssayProblem", "ActTypeID", "SolutionPath", SolutionPath);
    return eID;
    //            dataInterface.getDatabaseInstance("CourseInstructor", "CourseID", "EmployeeID", courseID);

}

QString ControllerModelInterface::getSubmissionPath(QString SubmissionPath)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("GetSubmissionPath");
    QString eID = dataInterface->getDatabaseInstance("ActivityEssayProblem", "ActTypeID", "SubmissionPath", SubmissionPath);
    return eID;
    //            dataInterface.getDatabaseInstance("CourseInstructor", "CourseID", "EmployeeID", courseID);

}

QString ControllerModelInterface::getFileName(QString fileName)
{
    ModelDataInterface *dataInterface = new ModelDataInterface("GetFileName");
    QString eID = dataInterface->getDatabaseInstance("EssayProblemFile", "ActTypeID", "FileName", fileName);
    return eID;
    //            dataInterface.getDatabaseInstance("CourseInstructor", "CourseID", "EmployeeID", courseID);

}

