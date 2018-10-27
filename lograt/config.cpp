#include "config.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "columnconfig.h"

namespace
{
    const auto DEFAULT_CONFIG_NAME = QString{"config.json"};
    const auto KEY_SCHEME = QString{"scheme"};
    const auto KEY_STATIC_COLUMNS_REGEXP = QString{"static_columns_regexp"};
    const auto KEY_STATIC_COLUMN_WIDTHS = QString{"static_columns_widths"};
} // namespace

Config::Config(QObject *parent) : QObject(parent) {}

void Config::open()
{
    QFile file{DEFAULT_CONFIG_NAME};
    if (!file.exists())
    {
        qDebug() << "file does not exist: " << DEFAULT_CONFIG_NAME;
        return;
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "failed to open file: " << DEFAULT_CONFIG_NAME;
        return;
    }

    const auto bytes = file.readAll();
    file.close();

    if (bytes.length() == 0)
    {
        qDebug() << "file is empty: " << DEFAULT_CONFIG_NAME;
        return;
    }

    const auto doc = QJsonDocument::fromJson(bytes.data());
    if (!doc.isObject())
    {
        qDebug() << "config should be JSON object";
        return;
    }

    const auto rootObj = doc.object();

    // required: "scheme"
    if (!rootObj.contains(KEY_SCHEME))
    {
        qDebug() << "config missing scheme key";
        return;
    }

    _scheme = rootObj.value(KEY_SCHEME).toString();

    if (rootObj.contains(KEY_STATIC_COLUMNS_REGEXP))
    {
        const auto regExpStr = rootObj.value(KEY_STATIC_COLUMNS_REGEXP).toString();
        _staticColumnsRegexp = QRegularExpression{regExpStr};
        if (!_staticColumnsRegexp.isValid())
        {
            qDebug() << "invalid RegExp: " << regExpStr;
            _staticColumnsRegexp = QRegularExpression{".*"};
            return;
        }

        // drop first name will be empty
        auto columnsNames = _staticColumnsRegexp.namedCaptureGroups();
        if (columnsNames.size() < 2)
        {
            qDebug() << "no named groups found. default behavior not "
                        "implemented, yet. Bailing out.";
            return;
        }
        columnsNames.pop_front();

        for (const auto &name : columnsNames)
        {
            auto col = new ColumnConfig(this);
            col->setName(name);
            _columns << col;
        }
    }

    // parse individual ColumnConfigs
    for (const auto col : _columns)
    {
        if (!rootObj.contains(col->name()))
        {
            qDebug() << "no column config found for " << col->name() << ". Using default.";
            col->setWidth(100);
            continue;
        }

        const auto obj = rootObj.value(col->name()).toObject();
        col->setValues(obj);
    }
}
