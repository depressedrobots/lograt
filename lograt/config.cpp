#include "config.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

namespace
{
    const auto DEFAULT_CONFIG_NAME = QString{"config.json"};
    const auto KEY_SCHEME = QString{"scheme"};
    const auto KEY_STATIC_COLUMNS_REGEXP = QString{"static_columns_regexp"};
    const auto KEY_STATIC_COLUMN_WIDTHS = QString{"static_columns_widths"};
}

Config::Config(QObject *parent) : QObject(parent) {}

void Config::open()
{
    QFile file{DEFAULT_CONFIG_NAME};
    if( !file.exists())
    {
        qDebug() << "file does not exist: " << DEFAULT_CONFIG_NAME;
        return;
    }

    if( !file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to open file: " << DEFAULT_CONFIG_NAME;
        return;
    }

    const auto bytes = file.readAll();
    file.close();

    if( bytes.length() == 0 )
    {
        qDebug() << "file is empty: " << DEFAULT_CONFIG_NAME;
        return;
    }

    const auto doc = QJsonDocument::fromJson(bytes.data());
    if( !doc.isObject())
    {
        qDebug() << "config should be JSON object";
        return;
    }

    const auto rootObj = doc.object();

    // required: "scheme"
    if(!rootObj.contains(KEY_SCHEME))
    {
        qDebug() << "config missing scheme key";
        return;
    }

    _scheme = rootObj.value(KEY_SCHEME).toString();

    if( rootObj.contains(KEY_STATIC_COLUMNS_REGEXP))
    {
        const auto regExpStr = rootObj.value(KEY_STATIC_COLUMNS_REGEXP).toString();
        _staticColumnsRegexp = QRegularExpression{regExpStr};
        if( !_staticColumnsRegexp.isValid() )
        {
            qDebug() << "invalid RegExp: " << regExpStr;
            _staticColumnsRegexp = QRegularExpression{".*"};
            return;
        }

        // drop first name as it will be empty
        _staticColumnsNames = _staticColumnsRegexp.namedCaptureGroups();
        if( !_staticColumnsNames.isEmpty())
            _staticColumnsNames.pop_front();
    }

    if( rootObj.contains(KEY_STATIC_COLUMN_WIDTHS))
    {
        const auto obj = rootObj.value(KEY_STATIC_COLUMN_WIDTHS);
        if( !obj.isArray())
            qDebug() << "found " << KEY_STATIC_COLUMN_WIDTHS << " but it wasn't an array";
        else
        {
            _columnWidths.clear();
            const auto arr = obj.toArray();
            for(const auto& val : arr)
            {
                if( !val.isDouble())
                {
                    qDebug() << "value in " << KEY_STATIC_COLUMN_WIDTHS << " array is not a number: " << val;
                    continue;
                }
                _columnWidths << val.toInt();
            }
        }
    }
}
