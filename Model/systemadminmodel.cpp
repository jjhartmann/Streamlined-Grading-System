#include "Model/systemadminmodel.h"

SystemAdminModel::SystemAdminModel()
{
}


bool SystemAdminModel::sysadminCreateAccount(QString employeeID, QString username, QString password, QString firstname, QString lastname, bool chkbxInstructor,
                                             bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin){
    bool error= false;
    ModelDataInterface dataInterface("SysAdminCreateConnect");

    error = dataInterface.insertAccount(employeeID, username, password, firstname, lastname);

    if(chkbxAcademicAdmin == true){
        error = dataInterface.addAccountTypeAcademicAdmin(employeeID);
    }
    if(chkbxAdminAssistant == true){
        error = dataInterface.addAccountTypeAdminAssistent(employeeID);
    }
    if(chkbxInstructor == true){
        error = dataInterface.addAccountTypeInstructor(employeeID);
    }
    if(chkbxSysAdmin == true){
        error = dataInterface.addAccountTypeSysAdmin(employeeID);
    }
    if(chkbxTA == true){
        error = dataInterface.addAccountTypeTATM(employeeID);
    }

    return error;
}

bool SystemAdminModel::sysadminModifyAccount(QString employeeID, QString username, QString firstname, QString lastname, bool chkbxInstructor,
                                             bool chkbxTA, bool chkbxAcademicAdmin, bool chkbxAdminAssistant, bool chkbxSysAdmin,
                                             bool currentchkbxInstructor, bool currentchkbxTA, bool currentchkbxAcademicAdmin, bool currentchkbxAdminAssistant, bool currentchkbxSysAdmin){
    bool error= false;
    ModelDataInterface dataInterface("SysAdminModifyConnect");

    error = dataInterface.updateAccountAllAttributes(employeeID, username, firstname, lastname);

    if(chkbxAcademicAdmin != currentchkbxAcademicAdmin)
    {
        if(chkbxAcademicAdmin == true){
            error = dataInterface.addAccountTypeAcademicAdmin(employeeID);
        } else {
            error = dataInterface.deleteAccountRoleAcademic(employeeID);
        }
    }

    if(chkbxAdminAssistant != currentchkbxAdminAssistant)
    {
        if(chkbxAdminAssistant == true){
            error = dataInterface.addAccountTypeAdminAssistent(employeeID);
        } else {
            error = dataInterface.deleteAccountRoleAdminAssist(employeeID);
        }
    }

    if(chkbxInstructor != currentchkbxInstructor)
    {
        if(chkbxInstructor == true){
            error = dataInterface.addAccountTypeInstructor(employeeID);
        } else {
            error = dataInterface.deleteAccountRoleInstructor(employeeID);
        }
    }

    if(chkbxSysAdmin != currentchkbxSysAdmin)
    {
        if(chkbxSysAdmin == true){
            error = dataInterface.addAccountTypeSysAdmin(employeeID);
        } else {
            error = dataInterface.deleteAccountRoleSysAdmin(employeeID);
        }
    }

    if(chkbxTA != currentchkbxTA)
    {
        if(chkbxTA == true){
            error = dataInterface.addAccountTypeTATM(employeeID);
        } else {
            error = dataInterface.deleteAccountRoleTATM(employeeID);
        }
    }

    return error;
}
