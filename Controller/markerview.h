#ifndef MARKERVIEW_H
#include "Controller/controllermodelinterface.h"
#include "markers.h"
#define MARKERVIEW_H

#include <QMainWindow>

namespace Ui {
class MarkerView;
}

class MarkerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkerView(QWidget *parent = 0);
    ~MarkerView();
    void initMarkerView(QString username, QString eID);
    //QString getActivityID(const QModelIndex &index);

signals:
    void signal_markerLogOff();

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_markSubmission_clicked();

    void on_actionLogout_triggered();
    void refreshTableView();

    void on_tableView_CourseSelection_clicked(const QModelIndex &index);

    void on_tableView_Activities_clicked(const QModelIndex &index);

private:
    Ui::MarkerView *ui;

    QString Selection;
    QString activitySelection;
    QString selectedCourseID;
    markers *Markers;
    // 'interface' is the go-between for the controller and the model
    ControllerModelInterface *interface;
    QSqlQueryModel *querymodel;
    QString markerUsername;
    QString markerEmployeeID;
};

#endif // MARKERVIEW_H
