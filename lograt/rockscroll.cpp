#include "rockscroll.h"

RockScroll::RockScroll(QQuickItem *parent) : QQuickPaintedItem{parent} { setFillColor(Qt::green); }

void RockScroll::paint(QPainter *painter) {}
