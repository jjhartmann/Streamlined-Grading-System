#ifndef CONTROLLERCREATEACTIVITYWIZARD_H
#include "formcreateactivitywizard.h"
#define CONTROLLERCREATEACTIVITYWIZARD_H

//#include <QObject>
#include <QString>
#include <QFileDialog>

class ControllerCreateActivityWizard
{
//    Q_OBJECT
public:
     ControllerCreateActivityWizard(QString activityType, QString username, QString CourseID);
    ~ControllerCreateActivityWizard();

    void initFormWizard(int activityIndex);

private slots:
    void slot_pushbutton_cancelClick();
    void slot_pushbutton_confirmClick();


private:
    //Vars:
    QString globalActivityType;
    QString instructorUsername;
    QString globalCourseID;
    FormCreateActivityWizard *activityWizard;

    //FUNCTIONS
     QString fileDialogFolder();

};

#endif // CONTROLLERCREATEACTIVITYWIZARD_H
