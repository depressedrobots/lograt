#include "loglinesmodel.h"

LogLinesModel::LogLinesModel(QObject *parent) : QAbstractListModel(parent)
{

}

int LogLinesModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant LogLinesModel::data(const QModelIndex &index, int /*role*/) const
{
    return {"dummy"};
}
