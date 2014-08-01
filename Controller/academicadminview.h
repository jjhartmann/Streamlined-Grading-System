#ifndef ACADEMICADMINVIEW_H
#define ACADEMICADMINVIEW_H

#include <QMainWindow>
#include "Controller/controllermodelinterface.h"

namespace Ui {
class AcademicAdminView;
}

class AcademicAdminView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AcademicAdminView(QWidget *parent = 0);
    ~AcademicAdminView();

signals:
    void signal_academicAdminLogOff();

private slots:
    void on_actionLog_off_triggered();

private:
    Ui::AcademicAdminView *ui;

    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;

};

#endif // ACADEMICADMINVIEW_H
