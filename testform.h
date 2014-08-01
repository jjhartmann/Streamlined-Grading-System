#ifndef TESTFORM_H
#define TESTFORM_H
#include "Model/modeldatainterface.h"
#include <QWidget>

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestForm *ui;
    ModelDataInterface model;
};

#endif // TESTFORM_H
