/* Contains functions for assigning/removingTATM form */

#include "Controller/formmanageta.h"
#include "ui_formmanageta.h"

FormManageTA::FormManageTA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormManageTA)
{
    ui->setupUi(this);

    this->setWindowTitle("Manage TA/TM");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FormManageTA::~FormManageTA()
{
    delete ui;
}

void FormManageTA::initTAListGui(QString courseID, QString courseName)
{
    selectedCourseID = courseID;
    selectedCourseName = courseName;
    ui->label_courseName->setText(selectedCourseName);
    refreshList();

}

void FormManageTA::on_pushButton_addTA_clicked()
{
    QString employeeID = ui->lineEdit_empolyeeID->text();
    emit signalManageTA_add(employeeID);
    refreshList();
}

void FormManageTA::on_pushButton_deleteTA_clicked()
{
    QString employeeID = ui->lineEdit_empolyeeID->text();
    emit signalManageTA_delete(selectedCourseID, employeeID);
    refreshList();
}

void FormManageTA::on_pushButton_goBack_clicked()
{
    emit signalManageTA_goBack();
}

// Show/refresh the table model in form
void FormManageTA::refreshList()
{
    listModel = interface->getTAList(selectedCourseID);
    ui->tableView->setModel(listModel);
    ui->tableView->resizeColumnsToContents();
}

// Convert selection from table model to appear on screen
void FormManageTA::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_empolyeeID->setText(ui->tableView->model()->index(index.row(),1).data().toString());
}
