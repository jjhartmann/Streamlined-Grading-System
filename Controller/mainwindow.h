#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "forminstructor.h"
#include "formadminassistant.h"
#include "formsysadmin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // MainWindows for Various Views
    // When instantiating, make sure they are pointers!
    FormInstructor *InstructorWindow;
    FormAdminAssistant *AdminAssitWindow;
    FormSysAdmin *SysAdminWindow;


};

#endif // MAINWINDOW_H
