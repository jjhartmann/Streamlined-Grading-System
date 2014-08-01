/* Contains function for the assignStudentList form

   Using fucntion from http://qt-project.org/forums/viewthread/6893
   Implementation of .CSV file
*/

#include "Controller/formassignstudentlist.h"
#include "ui_formassignstudentlist.h"


FormAssignStudentList::FormAssignStudentList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAssignStudentList)
{
    ui->setupUi(this);
    ui->progressBar->hide();

}

FormAssignStudentList::~FormAssignStudentList()
{
    delete ui;

    //if(model != NULL){
  //      if(model->hasChildren()){
//
//            QObjectList items = model->children();

//            QMessageBox box;
//            box.setText("Delete Children");
//            box.exec();
      //  }else{
        //    delete model;
          //  model = 0;
           // QMessageBox box;
//            box.setText("Delete Model");
//            box.exec();
//        }
//    }


}

void FormAssignStudentList::initStudentForm(QString courseID)
{
    globalCourseID = courseID;
}

void FormAssignStudentList::on_pushButton_getPath_clicked()
{
    QFileDialog dialog;
    filename = dialog.getOpenFileName(this, "Student Selection .CSV", "home/","Comma Seperated Value(*.csv)");
    ui->lineEdit_editPath->setText(filename);



    if(filename != NULL){
        processCSVFile(filename);
        ui->tableView_student->setModel(model);
    }

}

void FormAssignStudentList::on_pushButton_goBack_clicked()
{
    this->close();
    emit signalStudentList_goback();
}

void FormAssignStudentList::on_pushButton_confirmStudents_clicked()
{
    for(int i=0 ;i< model->rowCount();i++){
        QString StudentID = model->index(i,2).data().toString();
        StudentID.chop(1);

        if(kmodel.checkStudent(StudentID)){

            qDebug()<<"checkmodel:"<<kmodel.checkStudent(StudentID);
            kmodel.insertStudentCourse(globalCourseID,StudentID);
        }
        else{
            kmodel.insertStudent(StudentID, model->index(i,0).data().toString(),model->index(i,1).data().toString());
            kmodel.insertStudentCourse(globalCourseID,StudentID);
        }

    }
    this->close();
    emit signalStudentList_confirm(strVec);
}

//****************************************************
// PRIVATE FUNCTIONS
void FormAssignStudentList::slotFileSelectedSuccessfully(QString filename){
    QMessageBox box;

    box.setText(filename);
    box.exec();

//    processCSVFile(filename);

//    if(model != NULL){
//    ui->listView_student->setModel(model);
//    }

}

void FormAssignStudentList::processCSVFile(QString filename){
    QFile file(filename);
    int length = 0;
    int currentprogress = 0;

    int j = 0;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //Get length
        while(!file.atEnd()){
            file.readLine();
            length++;
        }
    }
    file.close();

    ui->progressBar->show();
    ui->progressBar->setMaximum(length);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        model = new QStandardItemModel(length, 3);

        while(!file.atEnd()){
            QString line = file.readLine();
            QStringList elements = line.split(",");

            //Set elements in row
            for(int i = 0; i < 3; i++){
                QStandardItem *item = new QStandardItem;
                item->setText(elements.at(i));
                model-> setItem(j, i, item);
                strVec.push_back(elements.at(i));

            }//FOR LOOP

            ui->progressBar->setValue(currentprogress++);
            j++;
        } //while LOOP
    } //if statemtn

    ui->progressBar->hide();

}
void FormAssignStudentList::processLine(QString line){
    QStringList strings = line.split(",");


}

