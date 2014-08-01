#ifndef FORMASSIGNSTUDENTLIST_H
#define FORMASSIGNSTUDENTLIST_H

#include <QWidget>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include "Model/modeldatainterface.h"

namespace Ui {
class FormAssignStudentList;
}

class FormAssignStudentList : public QWidget
{
    Q_OBJECT

public:
    explicit FormAssignStudentList(QWidget *parent = 0);
    ~FormAssignStudentList();

    void initStudentForm(QString courseID);
signals:
    void signalStudentList_confirm(QVector<QString> vector);
    void signalStudentList_goback();

private slots:
    //CUSTOM SLOTs

    //END
    void on_pushButton_getPath_clicked();

    void on_pushButton_goBack_clicked();

    void on_pushButton_confirmStudents_clicked();

private:
    Ui::FormAssignStudentList *ui;
    QString filename;
    QStandardItemModel *model;
    QVector<QString> strVec;
    ModelDataInterface kmodel;
    QString globalCourseID;


    
    //Functons
    void processCSVFile(QString filename);
    void processLine(QString line);
    void slotFileSelectedSuccessfully(QString filename);
};

#endif // FORMASSIGNSTUDENTLIST_H
