#include "Model/modeldatainterface.h"
#include <QMessageBox>

ModelDataInterface::ModelDataInterface()
{
    connectionString = QString("DRIVER={SQL SERVER};"
                               "SERVER=cypress.csil.sfu.ca;"
                               "UID=c275g05;"
                               "PWD=bY4aJHJ2Jyy73PNn");
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connectionString);


    // Open the database
    db.open();
}

ModelDataInterface::ModelDataInterface(QString connectionName)
{
    connectionString = QString("DRIVER={SQL SERVER};"
                               "SERVER=cypress.csil.sfu.ca;"
                               "UID=c275g05;"
                               "PWD=bY4aJHJ2Jyy73PNn");
    db = QSqlDatabase::addDatabase("QODBC", connectionName);
    db.setDatabaseName(connectionString);


    // Open the database
    db.open();
}


ModelDataInterface::~ModelDataInterface(){
    //Auto closes database when out-of-scope
    db.close();
    QString connection = db.connectionName();
    db.removeDatabase(connection);
}

// **********************************************************
// INSERT FUNCTIONS


//******* ACCOUNTS

bool ModelDataInterface::insertAccount(QString employeeID, QString username, QString password, QString firstName, QString surName, QString accountTypeTable){
    bool dberror = false;
    QString query1 = "INSERT INTO Account(EmployeeID, UserName, password, FirstName, SurName) VALUES ("
            + employeeID + ", '" + username + "', '" + password +"', '" + firstName + "', '" + surName + "' )";
    insertQuerytoDatabase(query1);


    QString query2 = "INSERT INTO "+ accountTypeTable + " VALUES (" + employeeID +  ")";
    insertQuerytoDatabase(query2);

    return dberror;
}

bool ModelDataInterface::insertAccount(QString employeeID, QString username, QString password, QString firstName, QString surName){
    bool dberror = false;
    QString query1 = "INSERT INTO Account(EmployeeID, UserName, password, FirstName, SurName) VALUES ("
            + employeeID + ", '" + username + "', '" + password +"', '" + firstName + "', '" + surName + "' )";
    dberror = insertQuerytoDatabase(query1);

    return dberror;
}


bool ModelDataInterface::addAccountTypeInstructor(QString employeeID){
    QString query1 = "INSERT INTO AccountInstructor VALUES (" + employeeID + ")";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::addAccountTypeTATM(QString employeeID){
    QString query1 = "INSERT INTO AccountTATM VALUES (" + employeeID + ")";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::addAccountTypeAdminAssistent(QString employeeID){
    QString query1 = "INSERT INTO AccountAdminAssistant VALUES (" + employeeID + ")";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::addAccountTypeAcademicAdmin(QString employeeID){
    QString query1 = "INSERT INTO AccountAcademicAdmin VALUES (" + employeeID + ")";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::addAccountTypeSysAdmin(QString employeeID){
    QString query1 = "INSERT INTO AccountSysAdmin VALUES (" + employeeID + ")";
    return insertQuerytoDatabase(query1);
}

//***** STUDENT

bool ModelDataInterface::insertStudent(QString studentID, QString FName, QString SurName){
    QString query1 = "INSERT INTO Student VALUES ('" + studentID + "', '" + FName + "', '" + SurName + "')";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::checkStudent(QString studentID){
     bool result = false;
     QString str = "SELECT * FROM Student WHERE StudentID = " + studentID;
     QSqlQuery query(str, db);
     int field = query.record().indexOf("StudentID");
     if (query.isNull(field))
     {
         result = true;
     }
     return result;
 }

bool ModelDataInterface::insertStudentCourse(QString courseID, QString studentID){
    QString query = "INSERT INTO CourseGrade(CourseID, StudentID) VALUES (" + courseID + "," + studentID + ")";
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::insertStudentRubricGrade(QString courseID, QString studentID){
    QString query = "INSERT INTO RubricGrade(CourseID, StudentID) VALUES (" + courseID + "," + studentID + ")";
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::insertStudentActivityGrade(QString courseID, QString studentID){
    QString query = "INSERT INTO ActivityGrade(CourseID, StudentID) VALUES (" + courseID + "," + studentID + ")";
    return insertQuerytoDatabase(query);
}




//***** COURSE

bool ModelDataInterface::assigningTAtoCourse(QString employeeID, QString CourseID){
    QString query1 = "INSERT INTO CourseTATM VALUES (" + CourseID +"," + employeeID + ")";
    return insertQuerytoDatabase(query1);
}


bool ModelDataInterface::assigningInstructortoCourse(QString employeeID, QString CourseID){
    QString query1 = "INSERT INTO CourseInstructor VALUES (" + CourseID +"," + employeeID + ")";
    return insertQuerytoDatabase(query1);
}


QString ModelDataInterface::insertCourseGetID(QString courseName, QString courseNumber, QString startDate, QString endDate){
    QString query1 = "INSERT INTO Course(CourseName, CourseNumber, StartDate, EndDate) VALUES ('"
            + courseName + "', '" + courseNumber + "', '" + startDate + "', '" + endDate + "' )";
    QString pass;
    if(db.isOpen()){
        QSqlQuery query(query1, db);
        query.first();
        pass = query.lastInsertId().toString();

        //Error
        checkForErrors(&query);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    return pass;
}

//***** GRADES
bool ModelDataInterface::insertCourseGrade(QString courseID, QString studentID, QString courseGrade){
    QString query1 = "INSERT INTO CourseGrade(CoureseID, StudentID, CourseGrade) VALUES ('"
            + courseID + "', '" + studentID + "', '" + courseGrade + "' )";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::insertRubricGrade(QString rubricID, QString studentID, QString rubricGradeInstance){
    QString query1 = "INSERT INTO RubricGrade(RubricID, StudentID, RubricGradeInstance) VALUES ("
            + rubricID + ", " + studentID + ", " + rubricGradeInstance + " )";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::insertActivityGrade(QString activityID, QString studentID, QString activityGrade){
    QString query1 = "INSERT INTO ActivityGrade(ActivityID, StudentID, ActivityGrade) VALUES ('"
            + activityID + "', '" + studentID + "', '" + activityGrade + "' )";
    return insertQuerytoDatabase(query1);
}


//*******************************************************
// ***************************** INSERT ACTIVITY FUNCTION

QString ModelDataInterface::insertActivitygetID(QString ActType, QString actName, QString actDescription, QString actLanguage, QString actDueDate, QString courseID){
    QString str = "INSERT Activity(ActivityType, Name, Description, Language, DueDate, CourseID) VALUES(?, ?, ?, ?, ?, ?)";
    QString pass = "";

    if(db.isOpen()){
        QSqlQuery query(db);
        query.prepare(str);
        query.bindValue(0, QString("'" + ActType + "'"));
        query.bindValue(1, QString("'" + actName + "'"));
        query.bindValue(2, QString("'" + actDescription + "'"));
        query.bindValue(3, QString("'" + actLanguage + "'"));
        query.bindValue(4, actDueDate);
        query.bindValue(5, courseID);

        if(!query.exec()){
            qDebug() << "NOT WORKING!! InsertActivityGetID in DataBaseModel.cpp";
        };
        pass = query.lastInsertId().toString();

        //Error
        checkForErrors(&query);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    return pass;
}

bool ModelDataInterface::insertActivity(QString activityType, QString name, QString language, QString courseID){
    QString query1 = "INSERT INTO Activity(ActivityType, Name, Language, CourseID) VALUES ('"
            + activityType + "', '" + name + "', '" + language + "', '" + courseID + "' )";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::insertActivity(QString ActivityType, QString Name, QString Description, QString Language, QString DueDate, QString courseID){

    QString query1 = "INSERT INTO Activity(ActivityType, Name, Description, Language, DueDate, CourseID) VALUES ('"
            + ActivityType + "', '" + Name + "', '" + Description + "', '" + Language + "', '" + DueDate + "', " + courseID + " )";
    return insertQuerytoDatabase(query1);

}


bool ModelDataInterface::insertActivityLatePenalty(QString dayspast, QString percentage, QString activityID){
    QString query1 = "INSERT INTO ActivityLatePenalty (DaysPast, PenaltyPercentage, ActivityID) VALUES ('"
            + dayspast + "', '" + percentage + "', '" + activityID + "' )";
    return insertQuerytoDatabase(query1);
}


bool ModelDataInterface::insertActivityEarlyBonus(QString daysbefore, QString percentage, QString activityID){
    QString query1 = "INSERT INTO ActivityEarlyBonus (DaysBefore, BonusPercentage, ActivityID) VALUES ('"
            + daysbefore + "', '" + percentage + "', " + activityID + " )";
    return insertQuerytoDatabase(query1);
}

 bool ModelDataInterface::insertRubric(QString number, QString name, QString description, QString weight, QString activityID){
     QString query1 = "INSERT INTO Rubric (NumberofPoints, Name, Description, Weight, ActivityID) VALUES ('"
             + number + "', '" + name + "', '" + description + "', '" + weight + "', " + activityID + " )";
     return insertQuerytoDatabase(query1);
 }

//****** ESSAY

bool ModelDataInterface::insertActivityEssayProblem(QString activityID, QString numberofFiles, QString solutionPath, QString submissionPath){
    QString query1 = "INSERT INTO ActivityEssayProblem VALUES ("
            + activityID + ", '" + numberofFiles + "', '" + solutionPath + "', '" + submissionPath + "' )";
    return insertQuerytoDatabase(query1);

}

bool ModelDataInterface::insertEssayProblemFile(QString fileName, QString fileType, QString activityID){
    QString query1 = "INSERT INTO EssayProblemFile (FileName, FileType, ActTypeID) VALUES ('"
            + fileName + "', '" + fileType + "', " + activityID + " )";
    return insertQuerytoDatabase(query1);
}


//****** MC

bool ModelDataInterface::insertActivityMultipleChoice(QString activityID, QString resultsPath){
    QString query1 = "INSERT INTO ActivityMultipleChoice VALUES ('"
            + activityID + "', '" + resultsPath + "' )";
    return insertQuerytoDatabase(query1);

}

 bool ModelDataInterface::insertAnswerKeyInstance(QString answer, QString weight, QString activityID){
     QString query1 = "INSERT INTO AnswerKeyMC (Answer, Weight, ActTypeID) VALUES ('"
             + answer + "', " + weight + ", " + activityID + " )";
     return insertQuerytoDatabase(query1);
    }



//***** Coding Assignment

bool ModelDataInterface::insertActivityCoding(QString activityID, QString enviroment, QString mTests){
    QString query1 = "INSERT INTO ActivityCoding VALUES ("
            + activityID + ", '" + enviroment + "', " + mTests + " )";
    return insertQuerytoDatabase(query1);
}


bool ModelDataInterface::insertCodingTest(QString name, QString description, QString numberofInputFiles, QString numberofOutputFiles, QString consoleInputFilePath, QString consoleOuputPath, QString consoleErrorFilePath, QString activityID){
    QString query1 = "INSERT INTO CodingTest(Name, Description, NumberofInputFiles, NumberofOutputFiles, ConsoleInputFilePath, ConsoleOutputFilePath, ConsoleErrorFilePath, ActTypeID) VALUES ('"
            + name + "', '"
            + description + "', "
            + numberofInputFiles + ", "
            + numberofOutputFiles  + ", '"
            + consoleInputFilePath  + "', '"
            + consoleOuputPath  + "', '"
            + consoleErrorFilePath  + "', "
            + activityID + " )";
    return insertQuerytoDatabase(query1);
}

 QString ModelDataInterface::insertCodingTestGetID(QString name, QString description, QString numberofInputFiles, QString numberofOutputFiles, QString consoleInputFilePath, QString consoleOuputPath, QString consoleErrorFilePath, QString activityID){
     QString str = "INSERT INTO CodingTest(Name, Description, NumberofInputFiles, NumberofOutputFiles, ConsoleInputFilePath, ConsoleOutputFilePath, ConsoleErrorFilePath, ActTypeID) VALUES ('"
             + name + "', '"
             + description + "', "
             + numberofInputFiles + ", "
             + numberofOutputFiles  + ", '"
             + consoleInputFilePath  + "', '"
             + consoleOuputPath  + "', '"
             + consoleErrorFilePath  + "', "
             + activityID + " )";
     QString pass;

     if(db.isOpen()){
         QSqlQuery query(str, db);

         pass = query.lastInsertId().toString();

         //Error
         checkForErrors(&query);
     } else {
         qDebug() << "ERROR: Connection not open";
     }

     return pass;
 }

bool ModelDataInterface::insertTestInputPath(QString fileName, QString fileType, QString inputPath, QString codeTestID){
    QString query1 = "INSERT INTO TestInputPath (FileName, FileType, InputPath, CodeTestID) VALUES ('"
            + fileName + "', '" + fileType + "', '" + inputPath  + "', " + codeTestID + " )";
    return insertQuerytoDatabase(query1);
}

bool ModelDataInterface::insertTestSolutionPath(QString fileName, QString fileType, QString solutionPath, QString codeTestID){
    QString query1 = "INSERT INTO TestSolutionPath (FileName, FileType, SolutionPath, CodeTestID) VALUES ('"
            + fileName + "', '" + fileType + "', '" + solutionPath  + "', " + codeTestID + " )";
    return insertQuerytoDatabase(query1);
}

 bool ModelDataInterface::insertTestSampleOutputFile(QString fileName, QString fileType, QString outputPath, QString codeTestID){
     QString query1 = "INSERT INTO TestSampleOutputFile (FileName, FileType, OutputPath, CodeTestID) VALUES ('"
             + fileName + "', '" + fileType + "', '" + outputPath  + "', " + codeTestID + " )";
     return insertQuerytoDatabase(query1);
 }




// **********************************************************
// SELECT (GET) FUNCTIONS
QString ModelDataInterface::getAccountPassword(QString username){
    QString str = "SELECT * FROM Account WHERE Account.UserName LIKE '" + username +  "'";
    QString pass;

    if(db.isOpen()){
        QSqlQuery query(str, db);
        query.first();
        pass = query.value(2).toString();

        //Error
        checkForErrors(&query, 2);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    return pass;
}

QString ModelDataInterface::getDatabaseInstance(QString dataTable, QString lookupAttribute, QString desiredAttribute, QString lookupValue){
    QString str = "SELECT * FROM " + dataTable + " WHERE " + dataTable + "." + lookupAttribute + " LIKE '" + lookupValue + "'";
    QString pass;

    if(db.isOpen()){
        QSqlQuery query(str, db);
        query.first();
        int fieldInt = query.record().indexOf(desiredAttribute);
        pass = query.value(fieldInt).toString();

        //Error
        checkForErrors(&query, fieldInt);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    return pass;

}

QString ModelDataInterface::getCourseIDfromCourse(QString courseName, QString courseNumber, QString startDate){
    QString str = "SELECT CourseID FROM Course WHERE CourseName = '" + courseName + "' AND CourseNumber = '" + courseNumber + "' AND StartDate = '" + startDate + "'";
    QString pass;

    if(db.isOpen()){
        QSqlQuery query(str, db);
        query.first();
        pass = query.value(0).toString();

        //Error
        checkForErrors(&query, 2);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    return pass;
}

QSqlQueryModel* ModelDataInterface::getAllUsers(){
    QString query = "SELECT UserName, EmployeeID, FirstName, SurName FROM Account";
    QSqlQueryModel *model;

    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("UserName"));

        // Error
        checkForErrors(model);


    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getAllCourses(){
    QString query = "SELECT * FROM Course";
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getActivityEssayProblemSubmissionPath(QString ActTypeID){
    QString query = "SELECT SubmissionPath FROM ActivityEssayProblem WHERE ActTypeID = " + ActTypeID;
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;


}

QSqlQueryModel* ModelDataInterface::getEssayProblemFileName(QString ActTypeID){
    QString query = "SELECT FileName FROM EssayProblemFile WHERE ActTypeID = " + ActTypeID;
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getInstructorSolutionPath(QString ActTypeID){
    QString query = "SELECT SolutionPath FROM ActivityEssayProblem WHERE ActTypeID = " + ActTypeID;
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getAllRubricwithActivityID(QString ActivityID){
    QString query = "SELECT * FROM Rubric WHERE ActivityID = " + ActivityID;
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getAllvarTablewithCondition(QString tableName, QString lookupAttribute, QString lookupValue){
    QString query = "SELECT * FROM " + tableName + " WHERE " + lookupAttribute + " = '" + lookupValue + "'";
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getAllvarTable(QString tableName){
    QString query = "SELECT * FROM " + tableName;
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getAllInstructorAccounts(){
    QString query = "SELECT UserName, FirstName, SurName FROM ACCOUNT JOIN AccountInstructor ON Account.EmployeeID = AccountInstructor.EmployeeID";
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

QSqlQueryModel* ModelDataInterface::getStudentsFromCourse(QString CourseID){
    QString query = "SELECT Student.StudentID FROM Student JOIN CourseGrade ON Student.StudentID = CourseGrade.StudentID WHERE CourseGrade.CourseID =" + CourseID;
QSqlQueryModel *model;
    if(db.open()){
        model = new QSqlQueryModel;
        model->setQuery(query,db);
         checkForErrors(model);
    }
    return model;
}

QSqlQueryModel* ModelDataInterface::getAllTaTmAccounts(){
    QString query = "SELECT UserName, FirstName, SurName FROM ACCOUNT JOIN AccountTATM ON Account.EmployeeID = AccountTATM.EmployeeID";
    QSqlQueryModel *model;


    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}


QVector<QString>* ModelDataInterface::getUserAccountTypes(QString userName){
    QString sqlquery = "SELECT AccountSysAdmin.AccountType, AccountTATM.AccountType, AccountInstructor.AccountType, AccountAdminAssistant.AccountType, AccountAcademicAdmin.AccountType FROM Account FULL OUTER JOIN AccountSysAdmin ON Account.EmployeeID = AccountSysAdmin.EmployeeID FULL OUTER JOIN AccountTATM ON Account.EmployeeID = AccountTATM.EmployeeID FULL OUTER JOIN AccountInstructor ON Account.EmployeeID = AccountInstructor.EmployeeID FULL OUTER JOIN AccountAdminAssistant ON Account.EmployeeID = AccountAdminAssistant.EmployeeID FULL OUTER JOIN AccountAcademicAdmin ON Account.EmployeeID = AccountAcademicAdmin.EmployeeID WHERE Account.UserName = '"
            + userName + "'";

    QVector<QString> *vector;

    if(db.isOpen()){
        QSqlQuery query(sqlquery, db);
        vector = new QVector<QString>;

        query.first();
        for(int i = 0; i < 5; i++){
            QString str = query.value(i).toString();

            //Errors
            //checkForErrors(&query, i);

            if(!query.isNull(i)){
                vector->push_back(str);
            }
        }


    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return vector;

}

QSqlQueryModel* ModelDataInterface::getAllCoursesForInstructor(QString employeeID){
    QString query = "SELECT * FROM Course JOIN CourseInstructor ON CourseInstructor.CourseID = Course.CourseID WHERE CourseInstructor.EmployeeID = " + employeeID;

    QSqlQueryModel *model;
    if(db.isOpen()){
        model = new QSqlQueryModel;
        model->setQuery(query, db);

        //Error
        checkForErrors(model);

    } else {
        qDebug() << "ERROR: Connection not open";
    };

    return model;

}

//GET: Check if an instuctor is in a course
//RETURN: BOOLEAN
bool ModelDataInterface::checkIfCoursehasInstructor(QString courseID){
    bool result = false;
    QString str = "SELECT * FROM Course FULL JOIN CourseInstructor ON CourseInstructor.CourseID = Course.CourseID WHERE Course.CourseID = " + courseID;
    QString pass;

    if(db.isOpen()){
        QSqlQuery query(str, db);

        query.first();
        int fieldInt = query.record().indexOf("EmployeeID");
        pass = query.value(fieldInt).toString();

        //Error
        checkForErrors(&query, fieldInt);
    } else {
        qDebug() << "ERROR: Connection not open";
    }

    if(pass != NULL){
        result = true;
    }
    return result;


}

// **********************************************************
// UPDATE TABLE FUNCTIONS
bool ModelDataInterface::updateAccountPasswordFlag(QString username, int flagValue){
    QString fValue = QString::number(flagValue);

    QString query = "UPDATE Account SET Account.PasswordFlag=" + fValue + " WHERE Account.UserName ='" + username + "'";
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::updateAccountPassword(QString employeeID, QString password){
    QString query = "UPDATE Account SET Account.password='" + password + "' WHERE Account.EmployeeID =" + employeeID;
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::updateDatabaseInstance(QString dataTable, QString setAttribute, QString lookupAttribute, QString lookupValue, QString setValue){
    QString query = "UPDATE " + dataTable + " SET " + dataTable + "." + setAttribute + " = " + setValue + " WHERE " + dataTable + "." + lookupAttribute + " = '" + lookupValue +"'";
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::updateAccountAllAttributes(QString employeeID, QString username, QString firstname, QString lastname){
    QString query = "UPDATE Account SET UserName = '" + username + "', FirstName = '" + firstname + "', SurName = '" + lastname + "' WHERE EmployeeID = " + employeeID;
    return insertQuerytoDatabase(query);
}

bool ModelDataInterface::updateCourseAltributes(QString courseID, QString courseName, QString courseNumber, QString startDate, QString endDate){
    QString query = "UPDATE Course SET CourseName= '" + courseName + "', CourseNumber= '" + courseNumber + "', StartDate = " + startDate + ", EndDate= " + endDate + " WHERE CourseID = " + courseID;
    return insertQuerytoDatabase(query);
}

//************************************************************
// DELETE FUNCTIONS
bool ModelDataInterface::deleteAccount(QString employeeID)
{
    QString query = "DELETE FROM Account WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAccountRoleInstructor(QString employeeID)
{
    QString query = "DELETE FROM AccountInstructor WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAccountRoleTATM(QString employeeID)
{
    QString query = "DELETE FROM AccountTATM WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAccountRoleAdminAssist(QString employeeID)
{
    QString query = "DELETE FROM AccountAdminAssistant WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAccountRoleSysAdmin(QString employeeID)
{
    QString query = "DELETE FROM AccountSysAdmin WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAccountRoleAcademic(QString employeeID)
{
    QString query = "DELETE FROM AccountAcademicAdmin WHERE EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteCourse(QString courseID)
{
    QString query = "DELETE FROM Course WHERE CourseID = " + courseID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteInstructorFromCourse(QString courseID)
{
    QString query = "DELETE FROM CourseInstructor WHERE CourseID = " + courseID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteAllTATMFromCourse(QString courseID)
{
    QString query = "DELETE FROM CourseTATM WHERE CourseID = " + courseID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteTATMFromCourse(QString courseID, QString employeeID)
{
    QString query = "DELETE FROM CourseTATM WHERE CourseID = " + courseID + " AND EmployeeID = " + employeeID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

bool ModelDataInterface::deleteActivity(QString activityID)
{
    QString query = "DELETE FROM Activity WHERE ActivityID = " + activityID;
    bool error = insertQuerytoDatabase(query);
    return error;
}

// **********************************************************
// PRIVATE FUNCTIONS

bool ModelDataInterface::insertQuerytoDatabase(QString query){
    bool dberror = false;
    //    qDebug() << query;
    if(db.isOpen()){

        QSqlQueryModel model;
        model.setQuery(query, db);

        //Error Check
        checkForErrors(&model);

    } else {
        qDebug() << "ERROR: Connection not open";
        dberror = true;
    };
    return dberror;
}


void ModelDataInterface::checkForErrors(QSqlQuery *query, int fieldInt){
//    if(query->isNull(fieldInt)){
//        QMessageBox box;
//        box.setText("Database query turned up empty :(");
//        box.exec();
//    }


    if(query->lastError().isValid()){
        QMessageBox box;
        box.setText(query->lastError().databaseText());
        box.exec();
    }
}


void ModelDataInterface::checkForErrors(QSqlQuery *query){
    if(query->lastError().isValid()){
        QMessageBox box;
        box.setText(query->lastError().databaseText());
        box.exec();
    }
}


void ModelDataInterface::checkForErrors(QSqlQueryModel *model){
    if(model->lastError().isValid()){
        QMessageBox box;
        box.setText(model->lastError().databaseText());
        box.exec();
    }

}

