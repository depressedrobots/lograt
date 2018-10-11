#ifndef LOGLINESMODEL_H
#define LOGLINESMODEL_H

#include <QAbstractListModel>
#include <QRegularExpression>

class LogLinesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString filename MEMBER _filename NOTIFY filenameChanged)

public:
    explicit LogLinesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void filenameChanged(const QString& filename);

public slots:

private slots:
    void initConfig();
    void loadFile(const QString& filename);

private:
    QString _filename;
    QRegularExpression _regExp;
    QVector<QStringList> _lines;
};

#endif // LOGLINESMODEL_H
