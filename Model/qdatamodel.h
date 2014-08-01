#ifndef QDATAMODEL_H
#define QDATAMODEL_H

#include <QAbstractTableModel>
#include <QVariantList>
#include <QObject>

class QDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QDataModel();
    int rowCount(const QModelIndex &) const {return numberofrows; }
    int columnCount(const QModelIndex &) const {return 3;}
    void my_append_data();

private:
    int numberofrows = 0;
};

#endif // QDATAMODEL_H
