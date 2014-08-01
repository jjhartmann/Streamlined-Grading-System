#ifndef FORMASSIGNINSTRUCTORTOCOURSE_H
#define FORMASSIGNINSTRUCTORTOCOURSE_H

#include <QWidget>

namespace Ui {
class FormAssignInstructortoCourse;
}

class FormAssignInstructortoCourse : public QWidget
{
    Q_OBJECT

public:
    explicit FormAssignInstructortoCourse(QWidget *parent = 0);
    ~FormAssignInstructortoCourse();

signals:
    void signalassignButtonClicked(QString instructorEID);
    void signalcancelButtonClicked();

private slots:
    void on_pushButton_assignInstructor_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::FormAssignInstructortoCourse *ui;
};

#endif // FORMASSIGNINSTRUCTORTOCOURSE_H
