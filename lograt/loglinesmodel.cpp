#include "loglinesmodel.h"

#include <QDebug>
#include <QFile>

namespace
{
}

LogLinesModel::LogLinesModel(QObject *parent) : QAbstractListModel(parent)
{
    _config.open();

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

    QVector<LogLine> newLines;

    QTextStream in{&file};
    while(!in.atEnd())
    {
        const auto str = in.readLine();
        const auto res = _config.staticColumnsRegexp().match(str);
        if( !res.hasMatch())
            continue;

        auto captures = res.capturedTexts();
        captures.pop_front();   // the first one is the full match, not interesting
        newLines << captures;
    }

    file.close();

    beginInsertRows( QModelIndex(), 0, newLines.count());
    _lines = newLines;
    endInsertRows();
}

QHash<int, QByteArray> LogLinesModel::roleNames() const
{
    auto roles = QHash<int, QByteArray>{};
    auto count = 0;
    for(const auto& role : _config.staticColumnsNames())
    {
        roles.insert(count, role.toUtf8());
        count++;
    }

    return roles;
}

int LogLinesModel::columnCount(const QModelIndex& /*index*/ ) const
{
    return _config.staticColumnsNames().size();
}

int LogLinesModel::rowCount(const QModelIndex& /*parent*/) const
{
    return _lines.size();
}

QVariant LogLinesModel::data(const QModelIndex &index, int role) const
{
    return {_lines.at(index.row()).at(role)};
}

QString LogLinesModel::columnName(const int col) const
{
    return _config.staticColumnsNames().at(col);
}
