#include "loglinesmodel.h"

#include <QDebug>
#include <QFile>

namespace
{
    const auto CONFIG_FILE_NAME = "lograt.conf";
    const auto DEFAULT_MATCH_STRING = "(.*)";
}

LogLinesModel::LogLinesModel(QObject *parent) : QAbstractListModel(parent)
{
    initConfig();

    connect(this, &LogLinesModel::filenameChanged, this, &LogLinesModel::loadFile);
}

void LogLinesModel::initConfig()
{
    QFile configFile{CONFIG_FILE_NAME};
    if( !configFile.exists())
    {
        qDebug() << "config file not found: " << CONFIG_FILE_NAME;
        return;
    }

    if( !configFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "found config file but failed to open it.";
        return;
    }

    QTextStream in{&configFile};
    while(!in.atEnd())
    {
        const auto line = in.readLine();
        if(line.startsWith("#"))
            continue;

        _regExp = QRegularExpression{line};
        break;
    }

    if(_regExp.isValid())
        qDebug() << "found valid config:" << _regExp;
    else
    {
        _regExp = QRegularExpression{DEFAULT_MATCH_STRING};
        qDebug() << "no valid config. using default";
    }
    configFile.close();
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

    QVector<QStringList> newLines;

    QTextStream in{&file};
    while(!in.atEnd())
    {
        const auto str = in.readLine();
        const auto res = _regExp.match(str);
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

int LogLinesModel::rowCount(const QModelIndex &parent) const
{
    return _lines.size();
}

QVariant LogLinesModel::data(const QModelIndex &index, int /*role*/) const
{
    return {_lines.at(index.row())};
}
