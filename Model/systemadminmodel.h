#ifndef SYSTEMADMINMODEL_H
#include "modeldatainterface.h"
#define SYSTEMADMINMODEL_H

class SystemAdminModel
{
public:
    SystemAdminModel();
    static bool sysadminCreateAccount(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                      bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin);
    static bool sysadminModifyAccount(QString employeeID, QString username, QString firstname, QString lastname, bool chkbxInstructor,
                                      bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin,
                                      bool currentchkbxInstructor, bool currentchkbxTA, bool currentchkbxAcademicAdmin, bool currentchkbxAdminAssistant, bool currentchkbxSysAdmin);


private:



};

#endif // SYSTEMADMINMODEL_H
