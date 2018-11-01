#pragma once

#include <QQuickPaintedItem>

class RockScroll : public QQuickPaintedItem
{
    Q_OBJECT
  public:
    RockScroll(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
};
