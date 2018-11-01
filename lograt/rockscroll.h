#pragma once

#include "loglinesmodel.h"
#include <QAbstractItemModel>
#include <QQuickPaintedItem>

class RockScroll : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(LogLinesModel *model MEMBER _model NOTIFY modelChanged)
    Q_PROPERTY(int contentHeight MEMBER _contentHeight NOTIFY viewportHeightChanged)
    Q_PROPERTY(int viewportHeight MEMBER _viewportHeight NOTIFY viewportHeightChanged)
    Q_PROPERTY(int viewportY MEMBER _viewportY NOTIFY viewportYChanged)

  public:
    RockScroll(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

  signals:
    void modelChanged();
    void contentHeightChanged();
    void viewportHeightChanged();
    void viewportYChanged();

  protected:
    void mousePressEvent(QMouseEvent *event) override;

  private:
    LogLinesModel *_model = nullptr;
    int _contentHeight = 0;
    int _viewportHeight = 0;
    int _viewportY = 0;
};
