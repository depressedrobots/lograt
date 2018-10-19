#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QVector>
#include <QRegularExpression>

class ColumnConfig;

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    QString scheme() const { return _scheme; }
    QRegularExpression staticColumnsRegexp() const { return _staticColumnsRegexp; }
    QVector<ColumnConfig*> columns() const { return _columns; }

signals:
    void configLoaded(const bool success);

public slots:
    void open();

private:
    QString _scheme;
    QRegularExpression _staticColumnsRegexp;
    QVector<ColumnConfig*> _columns;
};

#endif // CONFIG_H
