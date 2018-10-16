#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QVector>
#include <QRegularExpression>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    QString scheme() const { return _scheme; }
    QRegularExpression staticColumnsRegexp() const { return _staticColumnsRegexp; }
    QStringList staticColumnsNames() const { return _staticColumnsNames; }
    QVector<int> columnWidths() const { return _columnWidths; }

signals:
    void configLoaded(const bool success);

public slots:
    void open();

private:
    QString _scheme;
    QRegularExpression _staticColumnsRegexp;
    QStringList _staticColumnsNames;
    QVector<int> _columnWidths;
};

#endif // CONFIG_H
