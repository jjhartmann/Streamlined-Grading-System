// SOURECE: http://stackoverflow.com/questions/19993898/dynamically-add-data-to-qtableview

#include "Model/qdatamodel.h"

QDataModel::QDataModel()
{

}
void QDataModel::my_append_data()
{
    int row = rowCount(QModelIndex());
    insertRow(row);
    numberofrows++;
    //    foreach(const QVariant &item, data){
    //        setData(createIndex(row, 0), item, Qt::EditRole);
    //    };
}
