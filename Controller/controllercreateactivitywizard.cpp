#include "Controller/controllercreateactivitywizard.h"

ControllerCreateActivityWizard::ControllerCreateActivityWizard(QString activityType, QString username, QString CourseID)
{
    globalActivityType = activityType;
    instructorUsername = username;
    globalCourseID = CourseID;
}

ControllerCreateActivityWizard::~ControllerCreateActivityWizard(){

}


void ControllerCreateActivityWizard::initFormWizard(int activityIndex)
{
    activityWizard = new FormCreateActivityWizard(globalActivityType, instructorUsername, globalCourseID, activityIndex);
//    connect(activityWizard, SIGNAL(signal_pushbutton_cancelClick()), this, SLOT(slot_pushbutton_cancelClick()));
    activityWizard->show();
}


// FROM WIZARD
void ControllerCreateActivityWizard::slot_pushbutton_cancelClick()
{
    activityWizard->close();
    if(activityWizard != NULL){
        delete activityWizard;
        activityWizard = NULL;
    }
}




//PRIVATE FUNCTIONS
QString ControllerCreateActivityWizard::fileDialogFolder()
{
    QString fileName;
//    fileName = QFileDialog::getExistingDirectory(this, "Open Image", "/home/jana", QFileDialog::ShowDirsOnly);
    return fileName;
}
