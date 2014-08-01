/* Contains functions for the createActivityWizard form
 *
 * REFERENCES: http://stackoverflow.com/questions/13111669/yes-no-message-box-using-qmessagebox
 */

#include "Controller/formcreateactivitywizard.h"
#include "ui_formcreateactivitywizard.h"

FormCreateActivityWizard::FormCreateActivityWizard(QString actType, QString username, QString cID, int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateActivityWizard),
    activityType(actType),
    instructorUsername(username),
    courseID(cID),
    activityTypeIndex(index)
{
    ui->setupUi(this);
    globalIterator = 0;
    ui->tabWidget_MainWizard->setCurrentIndex(globalIterator);
    ui->label_username->setText(instructorUsername);
    ui->label_activityType->setText(activityType);
    ui->pushButton_Back->hide();
    ui->label_courseID->setText(courseID);
    ui->progressBar->hide();

    //Model

}

FormCreateActivityWizard::~FormCreateActivityWizard()
{
    delete ui;
}

void FormCreateActivityWizard::initGUI()
{
    switch (activityTypeIndex) {
    case 1:
        essayFileTypesNames = new QStandardItemModel(0, 2);
        essayFileTypesNames->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
        essayFileTypesNames->setHorizontalHeaderItem(1,new QStandardItem("File Type"));
        ui->tableView_essayprob_fileNamesTypes->setModel(essayFileTypesNames);
        ui->tableView_essayprob_fileNamesTypes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        break;
    case 2:
        problemSetFileTypesNames = new QStandardItemModel(0, 2);
        problemSetFileTypesNames->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
        problemSetFileTypesNames->setHorizontalHeaderItem(1, new QStandardItem("File Type"));
        ui->tableView_essayprob_fileNamesTypes->setModel(problemSetFileTypesNames);
        ui->tableView_essayprob_fileNamesTypes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        break;
    case 3:
        multipleChoiceAnswerKey = new QStandardItemModel(0, 2);
        multipleChoiceAnswerKey->setHorizontalHeaderItem(0, new QStandardItem("Answer (A, B, etc.)"));
        multipleChoiceAnswerKey->setHorizontalHeaderItem(1, new QStandardItem("Weight"));
        ui->tableView_mc_AnswerKey->setModel(multipleChoiceAnswerKey);
        ui->tableView_mc_AnswerKey->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        break;
    case 4:
        codingTest = new QStandardItemModel(0, 5);
        codingTest->setHorizontalHeaderItem(0, new QStandardItem("Name"));
        codingTest->setHorizontalHeaderItem(1, new QStandardItem("Description"));
        codingTest->setHorizontalHeaderItem(2, new QStandardItem("Console Input Path"));
        codingTest->setHorizontalHeaderItem(3, new QStandardItem("Console Output Path"));
        codingTest->setHorizontalHeaderItem(4, new QStandardItem("Console Eror Path"));
        ui->tableView_coding_codingTest->setModel(codingTest);
        ui->tableView_coding_codingTest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        break;

    }

    //Bonuse Marks
    bonusMarks = new QStandardItemModel(0, 2);
    bonusMarks->setHorizontalHeaderItem(0, new QStandardItem("Days Before the Due Date"));
    bonusMarks->setHorizontalHeaderItem(1, new QStandardItem("Bonus Amount (%)"));
    ui->tableView_earlybonus->setModel(bonusMarks);
    ui->tableView_earlybonus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Late Penalties
    latePenalty = new QStandardItemModel(0, 2);
    latePenalty->setHorizontalHeaderItem(0, new QStandardItem("Days Past the Due Date"));
    latePenalty->setHorizontalHeaderItem(1, new QStandardItem("Penalty Amount (%)"));
    ui->tableView_latepenalty->setModel(latePenalty);
    ui->tableView_latepenalty->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //RUBRIC
    rubric = new QStandardItemModel(0, 4);
    rubric->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    rubric->setHorizontalHeaderItem(1, new QStandardItem("Desciption"));
    rubric->setHorizontalHeaderItem(2, new QStandardItem("Weight"));
    rubric->setHorizontalHeaderItem(3, new QStandardItem("Points"));
    ui->tableView_rubric->setModel(rubric);
    ui->tableView_rubric->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

//****************************************************
// CREATE GENERAL ACTIVITY ID
bool FormCreateActivityWizard::createGeneralActivity(){
    bool result = false;
    QString actName = ui->lineEdit_main_name->text();
    QString actDescription = ui->textEdit_main_descrip->toPlainText();
    QString actLanguage = ui->comboBox_mai_language->currentText();
    QString actDueDate = ui->dateEdit_main_dueDate->text();

    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "Confirm", "This will create an activity for your course. Verify the information is correct.",
                                QMessageBox::Yes|QMessageBox::No);
    if (box == QMessageBox::Yes){

        emit signal_pushbutton_nextCreateGeneralActivity(activityType, actName, actDescription, actLanguage, actDueDate, courseID);
        result = true;
    }

    return result;

}

//************************************************************
//CREATE DETIALS
void FormCreateActivityWizard::on_pushButton_confirm_clicked()
{
    QString solutionPath;
    QString submissionPath;
    QString mcOutputPath;
    QString codingEnviroment;
    switch (activityTypeIndex) {
        case 1:
            solutionPath = ui->lineEdit_essay_solutionPath->text();
            submissionPath = ui->lineEdit_essay_submissionpath->text();
            emit signal_essay_confirm(solutionPath, submissionPath, essayFileTypesNames, bonusMarks, latePenalty, globalActivityID);
            break;
        case 2:
            solutionPath = ui->lineEdit_essay_solutionPath->text();
            submissionPath = ui->lineEdit_essay_submissionpath->text();
            emit signal_problemset_confirm(solutionPath, submissionPath, problemSetFileTypesNames, bonusMarks, latePenalty, globalActivityID);
            break;
        case 3:
            mcOutputPath = ui->lineEdit_mc_outputPath->text();
            emit signal_mc_confirm(mcOutputPath, multipleChoiceAnswerKey, bonusMarks, latePenalty, globalActivityID);
            break;
        case 4:
            codingEnviroment = ui->comboBox_coding_enviroment->currentText();
            emit signal_coding_confirm(codingEnviroment, codingTest, bonusMarks, latePenalty, globalActivityID);
            break;
    }

    //RUBRIC
    emit signal_rubric_additems(rubric, globalActivityID);
}


void FormCreateActivityWizard::delete_codingAssignmentTest_onCancel()
{
    on_pushButton_coding_delTest_clicked();
}

void FormCreateActivityWizard::setGlobalActivtyID(QString activityID)
{
    globalActivityID = activityID;
}


//*******************************************
// ESSAY AND PROBLEM SET PAGE
void FormCreateActivityWizard::on_pushButton_essayprob_addFiles_clicked()
{
    int row;
    switch (activityTypeIndex) {
    case 1:
        row = essayFileTypesNames->rowCount(QModelIndex());
        essayFileTypesNames->insertRow(row);
        break;
    case 2:
        row = problemSetFileTypesNames->rowCount(QModelIndex());
        problemSetFileTypesNames->insertRow(row);
        break;
    }

}

void FormCreateActivityWizard::on_pushButton_essayprob_delfiles_clicked()
{
    int row;
    switch (activityTypeIndex) {
    case 1:
        row = essayFileTypesNames->rowCount(QModelIndex());
        essayFileTypesNames->removeRow(row - 1);
        break;
    case 2:
        row = problemSetFileTypesNames->rowCount(QModelIndex());
        problemSetFileTypesNames->removeRow(row - 1);
        break;
    }
}

void FormCreateActivityWizard::on_pushButton_essayprob_browseSubPath_clicked()
{
    ui->lineEdit_essay_submissionpath->setText(fileDialogFolder());
}

void FormCreateActivityWizard::on_pushButton_essayprob_browseSolPath_clicked()
{
    ui->lineEdit_essay_solutionPath->setText(fileDialogFolder());
}

//*******************************************
// MULTIPLE CHOICE PAGE
void FormCreateActivityWizard::on_pushButton_mc_browseDir_clicked()
{
    ui->lineEdit_mc_outputPath->setText(fileDialogFolder());
}

void FormCreateActivityWizard::on_pushButton_mc_loadAnswerKey_clicked()
{

    QFileDialog dialog;
    QString filename = dialog.getOpenFileName(this, "Student Selection .CSV", "home/","Comma Seperated Value(*.csv)");

    if(filename != NULL){
        processCSVFile(filename);
        ui->tableView_mc_AnswerKey->setModel(multipleChoiceAnswerKey);
    }

}


//*******************************************
// CODING ASSIGNMENTS
void FormCreateActivityWizard::on_pushButton_codning_addTest_clicked()
{
    emit signal_pushbutton_codingTestADD();
}

void FormCreateActivityWizard::on_pushButton_coding_delTest_clicked()
{
    int row = codingTest->rowCount(QModelIndex());
    codingTest->removeRow(row - 1);
}

void FormCreateActivityWizard::setCodingTestRow(const QStandardItemModel  *generalItems){
    int col = generalItems->columnCount();
    int row = codingTest->rowCount();

    for(int i = 0; i < col; i++)
    {
        QStandardItem *item = new QStandardItem;
        item->setText(generalItems->index(0, i).data().toString());
        codingTest->setItem(row, i, item);
    }


}


//**********************************************
// LATE AND EARLY BONUS MARKS
void FormCreateActivityWizard::on_pushButton_earlybonus_add_clicked()
{
    int row = bonusMarks->rowCount(QModelIndex());
    if (row < 3){
        bonusMarks->insertRow(row);
    }
}

void FormCreateActivityWizard::on_pushButton_earlybonus_del_clicked()
{
    int row = bonusMarks->rowCount(QModelIndex());

    bonusMarks->removeRow(row - 1);
}

void FormCreateActivityWizard::on_pushButton_latepenalty_add_clicked()
{
    int row = latePenalty->rowCount(QModelIndex());
    if (row < 3){
        latePenalty->insertRow(row);
    }
}

void FormCreateActivityWizard::on_pushButton_latepenalry_del_clicked()
{
    int row = latePenalty->rowCount(QModelIndex());
    latePenalty->removeRow(row - 1);
}


//**********************************************
// RUBRIC FOR ACTIVITY

void FormCreateActivityWizard::on_pushButton_rubric_add_clicked()
{
    int row = rubric->rowCount(QModelIndex());
    rubric->insertRow(row);
}

void FormCreateActivityWizard::on_pushButton_rubric_delete_clicked()
{
    int row = rubric->rowCount(QModelIndex());
    rubric->removeRow(row - 1);
}

//**********************************************
// PRIVATE SLOTS NEXT AND BACK AND CANCEL BUTTON
void FormCreateActivityWizard::on_pushButton_Cancel_clicked()
{
    emit signal_pushbutton_cancelClick();

}

void FormCreateActivityWizard::on_pushButton_next_clicked()
{
    switch(activityTypeIndex){
    case 1:
        iteratorPloblemSetEssay();
        break;
    case 2:
        iteratorPloblemSetEssay();
        break;
    case 3:
        iteratorMultipleChoice();
        break;
    case 4:
        iteratorCodingAssignment();
        break;
    }

    ui->tabWidget_MainWizard->setCurrentIndex(globalIterator);

}

void FormCreateActivityWizard::on_pushButton_Back_clicked()
{
    switch(activityTypeIndex){
    case 1:
        iteratorPloblemSetEssay_back();
        break;
    case 2:
        iteratorPloblemSetEssay_back();
        break;
    case 3:
        iteratorMultipleChoice_back();
        break;
    case 4:
        iteratorCodingAssignment_back();
        break;
    }
    ui->tabWidget_MainWizard->setCurrentIndex(globalIterator);
}


//**************************************************************
//PRIVATE FUNCTIONS
void FormCreateActivityWizard::iteratorPloblemSetEssay(){
    //1 2 5 6
    switch(globalIterator){
    case 0:
        if(createGeneralActivity())
            globalIterator = 1;

            ui->pushButton_Back->hide();
            break;
        case 1:
            globalIterator = 4;
            ui->pushButton_Back->show();
            break;
        case 4:
            globalIterator = 5;
            break;
        case 5:
            globalIterator = 6;
            ui->pushButton_next->hide();

        break;
    }

}

void FormCreateActivityWizard::iteratorMultipleChoice(){
    //1 3 5 6
    switch(globalIterator){
        case 0:
            if(createGeneralActivity())
                globalIterator = 2;
            ui->pushButton_Back->hide();
            break;
        case 2:
                globalIterator = 4;
             ui->pushButton_Back->show();
            break;
        case 4:
            globalIterator = 5;
            break;
        case 5:
            globalIterator = 6;
            ui->pushButton_next->hide();

        break;
    }
}
void FormCreateActivityWizard::iteratorCodingAssignment(){
    //1 4 5 6
    switch(globalIterator){
    case 0:
        if(createGeneralActivity())
            globalIterator = 3;

        ui->pushButton_Back->hide();
        break;
        case 3:
            globalIterator = 4;
             ui->pushButton_Back->show();
            break;
        case 4:
            globalIterator = 5;
            break;
        case 5:
            globalIterator = 6;
            ui->pushButton_next->hide();

        break;
    }
}

void FormCreateActivityWizard::iteratorPloblemSetEssay_back(){
    //1 2 5 6
    switch(globalIterator){
        case 6:
            globalIterator = 5;
            ui->pushButton_next->show();
            break;
        case 5:
            globalIterator = 4;
            break;
        case 4:
            globalIterator = 1;
            ui->pushButton_Back->hide();
            break;
        case 1:
            globalIterator = 0;
            break;
    }

}

void FormCreateActivityWizard::iteratorMultipleChoice_back(){
    //1 3 5 6
    switch(globalIterator){
        case 6:
            globalIterator = 5;
            ui->pushButton_next->show();
            break;
        case 5:
            globalIterator = 4;
            break;
        case 4:
            globalIterator = 2;
            ui->pushButton_Back->hide();
            break;
        case 2:
            globalIterator = 0;
            break;
    }
}
void FormCreateActivityWizard::iteratorCodingAssignment_back(){
    //1 4 5 6
    switch(globalIterator){
        case 6:
            globalIterator = 5;
            ui->pushButton_next->show();
            break;
        case 5:
            globalIterator = 4;
            break;
        case 4:
            globalIterator = 3;
            ui->pushButton_Back->hide();
            break;
        case 3:
            globalIterator = 0;
            break;
    }
}

//File Folder Browser
QString FormCreateActivityWizard::fileDialogFolder()
{
    QString fileName;
    fileName = QFileDialog::getExistingDirectory(this, "Open Image", "/home/jana", QFileDialog::ShowDirsOnly);
    return fileName;
}



//********************************************
// PROCESS CSV FILE

void FormCreateActivityWizard::processCSVFile(QString filename){
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
        multipleChoiceAnswerKey = new QStandardItemModel(length, 2);

        while(!file.atEnd()){
            QString line = file.readLine();
            QStringList elements = line.split(",");

            //Set elements in row
            for(int i = 0; i < 2; i++){
                QStandardItem *item = new QStandardItem;
                item->setText(elements.at(i));
                multipleChoiceAnswerKey->setItem(j, i, item);

            }//FOR LOOP

            ui->progressBar->setValue(currentprogress++);
            j++;
        } //while LOOP
    } //if statemtn

    ui->progressBar->hide();

}






