#ifndef LOGLINESMODEL_H
#define LOGLINESMODEL_H

#include <QAbstractListModel>

class LogLinesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LogLinesModel(QObject *parent = nullptr);

signals:

public slots:

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // LOGLINESMODEL_H
