#ifndef FORMCREATECOURSE_H
#define FORMCREATECOURSE_H

#include <QWidget>

namespace Ui {
class FormCreateCourse;
}

class FormCreateCourse : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreateCourse(QWidget *parent = 0);
    ~FormCreateCourse();

signals:
    void signalButtonClicked_create(QString courseName, QString courseNumber, QString startDate, QString endDate, QString instructorEID);
    void signalBurronClicked_cancel();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_create_clicked();

private:
    Ui::FormCreateCourse *ui;
};

#endif // FORMCREATECOURSE_H
