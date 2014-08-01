#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T17:42:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StreamlinedGradingSystem
TEMPLATE = app



SOURCES += \
    main.cpp\
    Controller/loginview.cpp \
    Controller/instructorview.cpp \
    Controller/sysadminview.cpp \
    Controller/academicadminview.cpp \
    Controller/adminassistentview.cpp \
    Controller/markerview.cpp \
    Controller/controllermodelinterface.cpp \
    Model/modeldatainterface.cpp \
    testform.cpp \
    Controller/formchangepassword.cpp \
    Controller/viewcontroller.cpp \
    Controller/formadduseraccount.cpp \
    Controller/formassigninstructortocourse.cpp \
    Controller/formcreatecourse.cpp \
    Controller/formmanageta.cpp \
    Controller/formassignstudentlist.cpp \
    Controller/formselectmultipleaccounts.cpp \
    Model/systemadminmodel.cpp \
    Controller/formcreateactivitywizard.cpp \
    Controller/formcreateactivityselection.cpp \
    Controller/controllerforactivitywizard.cpp \
    Model/qdatamodel.cpp \
    Controller/formcreateactivitywizardcodingtests.cpp \
    Model/adminassistmodel.cpp \
    Model/instructormodel.cpp \
    Controller/studentmodel.cpp \
    Controller/markers.cpp


HEADERS  += \
    Controller/loginview.h \
    Controller/instructorview.h \
    Controller/sysadminview.h \
    Controller/academicadminview.h \
    Controller/adminassistentview.h \
    Controller/markerview.h \
    Controller/controllermodelinterface.h \
    enum.h \
    Model/modeldatainterface.h \
    testform.h \
    Controller/formchangepassword.h \
    Controller/viewcontroller.h \
    Controller/formadduseraccount.h \
    Controller/formassigninstructortocourse.h \
    Controller/formcreatecourse.h \
    Controller/formmanageta.h \
    Controller/formassignstudentlist.h \
    Controller/formselectmultipleaccounts.h \
    Model/systemadminmodel.h \
    Controller/formcreateactivitywizard.h \
    Controller/formcreateactivityselection.h \
    Controller/controllerforactivitywizard.h \
    Model/qdatamodel.h \
    Controller/formcreateactivitywizardcodingtests.h \
    Model/adminassistmodel.h \
    Model/instructormodel.h \
    Controller/studentmodel.h \
    Controller/markers.h


FORMS    += \
    View/loginview.ui \
    View/instructorview.ui \
    View/sysadminview.ui \
    View/academicadminview.ui \
    View/adminassistentview.ui \
    View/markerview.ui \
    testform.ui \
    View/formchangepassword.ui \
    View/formadduseraccount.ui \
    View/formassigninstructortocourse.ui \
    View/formcreatecourse.ui \
    View/formmanageta.ui \
    View/formassignstudentlist.ui \
    View/formselectmultipleaccounts.ui \
    View/formcreateactivitywizard.ui \
    View/formcreateactivityselection.ui \
    View/formcreateactivitywizardcodingtests.ui \
    View/markers.ui
