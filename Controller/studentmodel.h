#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H
#include "Controller/controllermodelinterface.h"

class studentmodel
{
public:
    studentmodel(QString courseID);
    void giveCourseId();

private:
    QString courseid;
};

#endif // STUDENTMODEL_H
