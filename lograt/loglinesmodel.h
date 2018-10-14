#ifndef LOGLINESMODEL_H
#define LOGLINESMODEL_H

#include <QAbstractListModel>
#include "config.h"

using LogLine = QStringList;

class LogLinesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString filename MEMBER _filename NOTIFY filenameChanged)

public:
    explicit LogLinesModel(QObject *parent = nullptr);

public slots:
    QHash<int, QByteArray> roleNames() const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString columnName(const int col) const;

signals:
    void filenameChanged(const QString& filename);

private slots:
    void loadFile(const QString& filename);

private:
    QString _filename;
    Config _config;
    QVector<LogLine> _lines;
};

#endif // LOGLINESMODEL_H
