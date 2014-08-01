/* Contain functions for marker main window UI view */

#include "Controller/markerview.h"
#include "ui_markerview.h"

MarkerView::MarkerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MarkerView)
{
    ui->setupUi(this);

    // Declare inferface objects for continued interactions
    interface = new ControllerModelInterface;
    this->setWindowTitle("Marker Main Window");
    ui->tableView_CourseSelection->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_Activities->setSelectionBehavior(QAbstractItemView::SelectRows);

    //markers = NULL;
}

MarkerView::~MarkerView()
{
    delete ui;
    delete interface;
}

void MarkerView::initMarkerView(QString username, QString eID){
    markerUsername = username;
    markerEmployeeID = eID;

    ui->label_userAccountName->setText(username);
    refreshTableView();
}

void MarkerView::on_comboBox_activated(int index)
{

}

void MarkerView::on_pushButton_markSubmission_clicked()
{
    QModelIndex currentIndex = ui->tableView_Activities->currentIndex();
    activitySelection = ui->tableView_Activities->model()->index(currentIndex.row(), 0).data().toString();

    Markers = new markers;
    Markers->setActivityID(activitySelection, Selection);
    Markers->displayRubric();
    Markers->show();

}

void MarkerView::on_actionLogout_triggered()
{
    emit signal_markerLogOff();
}

//PRIVATE FUNCTIONS
void MarkerView::refreshTableView(){

    querymodel = interface->getAllCoursefroInstructor(markerEmployeeID);
    ui->tableView_CourseSelection->setModel(querymodel);
    ui->tableView_CourseSelection->horizontalHeader()->setStretchLastSection(true);
}


void MarkerView::on_tableView_CourseSelection_clicked(const QModelIndex &index)
{
    Selection = ui->tableView_CourseSelection->model()->index(index.row(), 0).data().toString();
    querymodel = interface->getAllActivitiesInstructor(Selection);
    ui->tableView_Activities->setModel(querymodel);
    ui->tableView_CourseSelection->horizontalHeader()->setStretchLastSection(true);

//    selectedCourseID = ui->tableView_CourseSelection->model()->index(index.row(),0).data().toString();

}

void MarkerView::on_tableView_Activities_clicked(const QModelIndex &index)
{

}

