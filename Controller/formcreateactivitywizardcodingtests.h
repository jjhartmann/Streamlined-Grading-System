#ifndef FORMCREATEACTIVITYWIZARDCODINGTESTS_H
#define FORMCREATEACTIVITYWIZARDCODINGTESTS_H

#include <QStandardItemModel>
#include <QFileDialog>
#include <QWidget>

namespace Ui {
class FormCreateActivityWizardCodingTests;
}

class FormCreateActivityWizardCodingTests : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreateActivityWizardCodingTests(QWidget *parent = 0);
    ~FormCreateActivityWizardCodingTests();
    Ui::FormCreateActivityWizardCodingTests *ui;

signals:
    void signal_pusbutton_confirmClick(QStandardItemModel *generalItems, QStandardItemModel *solutionFiles, QStandardItemModel *submissionFiles, QStandardItemModel *outputFiles);
    void signal_pushbutton_cancelClick();


private slots:
    void on_pushButton_codingtest_inputPath_clicked();
    void on_pushButton_codingtest_outputPath_clicked();
    void on_pushButton_codingtest_errorpath_clicked();
    void on_pushButton_codingtest_solAdd_clicked();
    void on_pushButton_codingtest_solDel_clicked();
    void on_pushButton_codingtest_subAdd_clicked();
    void on_pushButton_codingtest_subDel_clicked();
    void on_pushButton_codingtest_outputAdd_clicked();
    void on_pushButton_codingtest_outputDel_clicked();
    void on_pushButton_confirm_clicked();
    void on_pushButton_Cancel_clicked();

private:
    //CONTAINERS
    QStandardItemModel *generalItems;
    QStandardItemModel *solutionFiles;
    QStandardItemModel *submissionFiles;
    QStandardItemModel *outputFiles;
    QVector<QStandardItemModel*> *codingTestCondensed;

    //FUNCTIONS
    QString fileDialogFolder();
};

#endif // FORMCREATEACTIVITYWIZARDCODINGTESTS_H
