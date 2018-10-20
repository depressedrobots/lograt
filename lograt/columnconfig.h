#pragma once

#include <QObject>
#include <QPair>
#include <QVector>
#include <QRegularExpression>

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

public slots:
    QString colorForString(const QString& str) const;
    void setValues(const QJsonObject& jsonObj);

private:
    QString _name;
    int _width = 0;
    QVector<QPair<QRegularExpression, QString>> _colors;
};
