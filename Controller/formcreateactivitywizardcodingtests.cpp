/* Contain functions for the createCodinTestsActivityWizard form */

#include "Controller/formcreateactivitywizardcodingtests.h"
#include "ui_formcreateactivitywizardcodingtests.h"

FormCreateActivityWizardCodingTests::FormCreateActivityWizardCodingTests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateActivityWizardCodingTests)
{
    ui->setupUi(this);
    generalItems = new QStandardItemModel(0, 5);
    generalItems->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    generalItems->setHorizontalHeaderItem(1, new QStandardItem("Description"));
    generalItems->setHorizontalHeaderItem(2, new QStandardItem("Console Input Path"));
    generalItems->setHorizontalHeaderItem(3, new QStandardItem("Console Output Path"));
    generalItems->setHorizontalHeaderItem(4, new QStandardItem("Console Error Path"));

    solutionFiles = new QStandardItemModel(0, 3);
    solutionFiles->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
    solutionFiles->setHorizontalHeaderItem(1, new QStandardItem("File Type"));
    solutionFiles->setHorizontalHeaderItem(2, new QStandardItem("Solution Path"));
    ui->tableView_codingtest_solPath->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_codingtest_solPath->setModel(solutionFiles);

    submissionFiles = new QStandardItemModel(0, 3);
    submissionFiles->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
    submissionFiles->setHorizontalHeaderItem(1, new QStandardItem("File Type"));
    submissionFiles->setHorizontalHeaderItem(2, new QStandardItem("Submission Path"));
    ui->tableView_codingtest_subPath->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_codingtest_subPath->setModel(submissionFiles);

    outputFiles = new QStandardItemModel(0, 3);
    outputFiles->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
    outputFiles->setHorizontalHeaderItem(1, new QStandardItem("File Type"));
    outputFiles->setHorizontalHeaderItem(2, new QStandardItem("Output Path"));
    ui->tableView_codingtest_outputPath->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_codingtest_outputPath->setModel(outputFiles);

}

FormCreateActivityWizardCodingTests::~FormCreateActivityWizardCodingTests()
{
    delete ui;
//    generalItems->deleteLater();
//    solutionFiles->deleteLater();
//    submissionFiles->deleteLater();
//    outputFiles->deleteLater();
}


// GENERAL MAIN PATH
void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_inputPath_clicked()
{
    ui->lineEdit_codingtest_inputpath->setText(fileDialogFolder());
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_outputPath_clicked()
{
    ui->lineEdit_codingtest_outputPath->setText(fileDialogFolder());
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_errorpath_clicked()
{
    ui->lineEdit_codingtest_errorPath->setText(fileDialogFolder());
}


// MAIN PAGE 2: FILE NAME AND PATHS
void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_solAdd_clicked()
{
    int row = solutionFiles->rowCount(QModelIndex());
    solutionFiles->insertRow(row);
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_solDel_clicked()
{
    int row = solutionFiles->rowCount(QModelIndex());
    solutionFiles->removeRow(row - 1);
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_subAdd_clicked()
{
    int row = submissionFiles->rowCount(QModelIndex());
    submissionFiles->insertRow(row);
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_subDel_clicked()
{
    int row = submissionFiles->rowCount(QModelIndex());
    submissionFiles->removeRow(row - 1);
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_outputAdd_clicked()
{
    int row = outputFiles->rowCount(QModelIndex());
    outputFiles->insertRow(row);
}

void FormCreateActivityWizardCodingTests::on_pushButton_codingtest_outputDel_clicked()
{
    int row = outputFiles->rowCount(QModelIndex());
    outputFiles->removeRow(row - 1);
}


//CONFIRM AND CANCEL
void FormCreateActivityWizardCodingTests::on_pushButton_confirm_clicked()
{
    QStandardItem *item = new QStandardItem();
    item->setText(ui->lineEdit_codingTest_name->text());
    generalItems->setItem(0, 0, item);

    QStandardItem *item2 = new QStandardItem();
    item2->setText(ui->textEdit_codingTest_description->toPlainText());
    generalItems->setItem(0, 1, item2);


    QStandardItem *item3 = new QStandardItem();
    item3->setText(ui->lineEdit_codingtest_inputpath->text());
    generalItems->setItem(0, 2, item3);

    QStandardItem *item4 = new QStandardItem();
    item4->setText(ui->lineEdit_codingtest_outputPath->text());
    generalItems->setItem(0, 3, item4);

    QStandardItem *item5 = new QStandardItem();
    item5->setText(ui->lineEdit_codingtest_errorPath->text());
    generalItems->setItem(0, 4, item5);

//    codingTestCondensed->push_back(generalItems);
//    codingTestCondensed->push_back(solutionFiles);
//    codingTestCondensed->push_back(submissionFiles);
//    codingTestCondensed->push_back(outputFiles);

    emit signal_pusbutton_confirmClick(generalItems, solutionFiles, submissionFiles, outputFiles);


}

void FormCreateActivityWizardCodingTests::on_pushButton_Cancel_clicked()
{
    emit signal_pushbutton_cancelClick();
}


//File Folder Browser
QString FormCreateActivityWizardCodingTests::fileDialogFolder()
{
    QString fileName;
    fileName = QFileDialog::getExistingDirectory(this, "Open Image", "/home/jana", QFileDialog::ShowDirsOnly);
    return fileName;
}

