#include "loglinesmodel.h"

#include <QDebug>
#include <QFile>

LogLinesModel::LogLinesModel(QObject *parent) : QAbstractListModel(parent)
{
    connect(this, &LogLinesModel::filenameChanged, this, &LogLinesModel::loadFile);
}

void LogLinesModel::loadFile(const QString& filename)
{
    qDebug() << "loading file: " << filename << " ...";
    if( !QFile::exists(filename))
    {
        qDebug() << "file not found";
        return;
    }

    QFile file{filename};
    if( !file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to open file";
        return;
    }

    QStringList newLines;

    QTextStream in{&file};
    while(!in.atEnd())
        newLines << in.readLine();

    file.close();

    beginInsertRows( QModelIndex(), 0, newLines.count());
    _lines = newLines;
    endInsertRows();
}

int LogLinesModel::rowCount(const QModelIndex &parent) const
{
    return _lines.size();
}

QVariant LogLinesModel::data(const QModelIndex &index, int /*role*/) const
{
    return {_lines.at(index.row())};
}
