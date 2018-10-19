#pragma once

#include <QObject>
#include <QPair>
#include <QVector>

class ColumnConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(int width MEMBER _width CONSTANT)

public:
    ColumnConfig(QObject* parent = nullptr) : QObject{parent} {}

    QString name() const { return _name; }
    void setName(const QString& name) { _name = name; }

    int width() const { return _width; }
    void setWidth(const int width) { _width = width; }

    QVector<QPair<QString, QString>> colors() const { return _colors; }

    void setValues(const QJsonObject& jsonObj);

private:
    QString _name;
    int _width = 0;
    QVector<QPair<QString, QString>> _colors;
};
