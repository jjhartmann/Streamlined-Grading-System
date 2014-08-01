#include "Controller\markers.h"
#include "ui_markers.h"

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

markers::markers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::markers)
{
    ui->setupUi(this);

    interface = new ControllerModelInterface;
}

markers::~markers()
{
    delete ui;
}

void markers::setActivityID(QString aID, QString courseID)
{
    activityID = aID;
    selectedCourseID = courseID;
    displayRubric();
    displayInstructorSolution();

}

void markers::displayRubric()
{
    interface = new ControllerModelInterface;
    rubrictable = interface->getAllRubricItems(activityID);
    studentmodel = interface->getStudentList(selectedCourseID);
    ui->tableView_Rubric->setModel(rubrictable);
    ui->tableView_StudentSelection->setModel(studentmodel);

}

void markers::on_pushButton_GradeEssayActivity_clicked()
{
    QModelIndex currentIndexrubric = ui->tableView_Rubric->currentIndex();
    QString studentID = ui->tableView_StudentSelection->model()->index(currentIndexrubric.row(), 0).data().toString();
    //QString studentID = "123";

    QModelIndex currentIndex = ui->tableView_Rubric->currentIndex();
    QString rubricID = ui->tableView_Rubric->model()->index(currentIndex.row(), 0).data().toString();
   //QString rubricID ="13";

    QString grade = ui->lineEdit->text();

    modeldatainterface = new ModelDataInterface;
    modeldatainterface->insertRubricGrade(rubricID , studentID, grade);

//    if (studentID != "")
//    {

//         QString grade = ui->lineEdit->text();
//        if(grade != "")
//        {
//           modeldatainterface = new ModelDataInterface;
//           modeldatainterface->insertRubricGrade(rubricID ,studentID, grade);
//        }
//        else
//        {
//           QMessageBox::information(this, tr("Error"), tr("Enter a grade"));
//        }

//    }
//    else
//    {
//        QMessageBox::information(this, tr("Error"), tr("Select a student from student list"));
//    }

}

void markers::on_tableView_StudentSelection_doubleClicked(const QModelIndex &index)
{
    QString studentID = ui->tableView_StudentSelection->model()->index(index.row(), 0).data().toString();

    interface = new ControllerModelInterface;
    QString submissionpath = interface->getSubmissionPath(activityID);
    QString testString = submissionpath.append("/");
    QString testString2 = testString.append(studentID);
    QString testString3 = testString2.append("/");
    QString filename = interface->getFileName(activityID);
    QString testString4 = testString3.append(filename);
    QDesktopServices::openUrl(QUrl(testString4.append(".pdf")));

}

void markers::StudentSubmissionList()
{
    //display students submissions (files)
    querymodel->setQuery(QObject::tr("SELECT FileName FROM EssayProblemFile"));

    ui->tableView_StudentSelection->setModel(querymodel);
}

void markers::displayInstructorSolution()
{
    interface = new ControllerModelInterface;
    QString instructorsolution = interface->getSolutionPath(activityID);
    QString filename = interface->getFileName(activityID);
   // QString finalPath = QDir(instructorsolution).filePath(filename);
    QString testString = instructorsolution.append("/");
    QString testString2 = testString.append(filename);
    QDesktopServices::openUrl(QUrl(testString2.append(".pdf")));
}

void markers::on_pushButton_OpenInstructorSolution_clicked()
{
    displayInstructorSolution();
}


