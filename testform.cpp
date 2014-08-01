#include "testform.h"
#include "ui_testform.h"
#include <QSqlDatabase>

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::on_pushButton_clicked()
{

    QString coursename = "CMPT";
    QString coursenum = "300A";
    QString sdate = "20120115";
    QString edate = "20120610";

    QString EmployeeID = "134012";
    QString username = "jre4";
    QString firstname = "hart";
    QString surname = "hart";
    QString accounttype = "AccountSysAdmin";
    QString password = "5464554";
    QString courseID = "10";


    QString flag = model.getDatabaseInstance("Account", "UserName", "PasswordFlag", "1222221");
    model.addAccountTypeTATM("123");
    QVector<QString> *vec = model.getUserAccountTypes("xsq");

    qDebug() << "Values: " << vec->length();
    qDebug() << "Value is: " << vec->at(0);

    ui->label->setText(flag);

    QSqlQueryModel *qmodel = new QSqlQueryModel;
    qmodel = model.getAllUsers();
    ui->tableView->setModel(qmodel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSortingEnabled(true);

    int index = ui->tableView->selectionModel()->currentIndex().row();
    ui->label->setText(QString::number(index));

    QSqlQueryModel *tmodel = model.getAllCourses();
    ui->treeView->setModel(tmodel);


    //    QString query;
    //    QString str = "jere";
    //    query = model.getAccountPassword(str);
    //    ui->label->setText(query);

}
