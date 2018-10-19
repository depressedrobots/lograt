#include "columnconfig.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace
{
    const auto KEY_WIDTH = "width";
    const auto KEY_COLORS = "colors";
    const auto KEY_COLOR = "color";
    const auto KEY_REGEXP = "regexp";
}

void ColumnConfig::setValues(const QJsonObject& jsonObj)
{
    if( jsonObj.contains(KEY_WIDTH))
        _width = jsonObj.value(KEY_WIDTH).toInt();

    if( jsonObj.contains(KEY_COLORS))
    {
        const auto arr = jsonObj.value(KEY_COLORS).toArray();
        for( const auto& colorObjVal : arr)
        {
            const auto colorObj = colorObjVal.toObject();
            if( !colorObj.contains(KEY_COLOR) || !colorObj.contains(KEY_REGEXP))
            {
                qDebug() << "incomplete color obj: " << colorObjVal;
                continue;
            }

            const auto pair = QPair<QString, QString>{colorObj.value(KEY_COLOR).toString(), colorObj.value(KEY_REGEXP).toString()};
            qDebug() << "found color pair: " << pair;

            _colors << pair;
        }
    }
}
