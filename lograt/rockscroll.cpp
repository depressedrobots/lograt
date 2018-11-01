#include "rockscroll.h"
#include "columnconfig.h"
#include <QDebug>
#include <QModelIndex>
#include <QPainter>

RockScroll::RockScroll(QQuickItem *parent) : QQuickPaintedItem{parent}
{
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setFillColor(Qt::black);

    connect(this, &RockScroll::modelChanged, [this] { update(); });
    connect(this, &RockScroll::viewportYChanged, [this] { update(); });
    connect(this, &RockScroll::viewportHeightChanged, [this] { update(); });
    connect(this, &RockScroll::contentHeightChanged, [this] { update(); });
}

void RockScroll::paint(QPainter *painter)
{
    if (nullptr == _model)
        return;

    const auto numLines = _model->rowCount();
    const auto pixelsPerLine = static_cast<float>(height()) / numLines;
    const auto colConfig = _model->columnConfig(0);

    for (auto row = 0; row < numLines; row++)
    {
        const auto index = _model->index(row, 0);
        const auto str = _model->data(index).toString();
        const auto colorStr = colConfig->colorForString(str);
        const auto color = QColor{colorStr};
        const auto currentPosY = static_cast<int>(row * pixelsPerLine);

        QPen pen{color, 1};
        painter->setPen(pen);
        painter->drawLine(0, currentPosY, static_cast<int>(width()), currentPosY);
    };

    if (_contentHeight <= 0 || _viewportHeight <= 0)
        return;

    qDebug() << "repainting viewport with contentHeight: " << _contentHeight << " viewportHeight: " << _viewportHeight;

    const auto screenToContentRatio = height() / _contentHeight;
    const auto viewportDrawHeight = _viewportHeight * screenToContentRatio;
    const auto viewportDrawY = _viewportY * screenToContentRatio;
    qDebug() << "ratio: " << screenToContentRatio;

    QPen pen{QColor{"red"}, 3};
    painter->setPen(pen);
    painter->drawRect(0, viewportDrawY, width(), viewportDrawHeight);
}

void RockScroll::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "received left mouse button event at: " << event->y();
}
