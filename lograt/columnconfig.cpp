#include "columnconfig.h"

#include <QJsonObject>

namespace
{
    const auto KEY_WIDTH = "width";
}

void ColumnConfig::setValues(const QJsonObject& jsonObj)
{
    if( jsonObj.contains(KEY_WIDTH))
        _width = jsonObj.value(KEY_WIDTH).toInt();
}
