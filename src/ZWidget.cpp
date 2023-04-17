#include "ZWidget.h"

#include <QEvent>
#include <QChildEvent>

ZWidget::ZWidget(QObject *parent)
    : QObject{parent}
{
}

void ZWidget::childEvent(QChildEvent *event)
{
    if (event->type() == QEvent::Type::ChildAdded) {
        addChild(event->child());
        if (auto *widget = dynamic_cast<ZWidget *>(event->child())) {
            emit widget->parentChanged(QPrivateSignal{});
        }
    } else if (event->type() == QEvent::Type::ChildRemoved) {
        removeChild(event->child());
        if (auto *widget = dynamic_cast<ZWidget *>(event->child())) {
            emit widget->parentChanged(QPrivateSignal{});
        }
    }
}

bool ZWidget::visible() const
{
    return m_visible;
}

void ZWidget::setVisible(bool on)
{
    if (m_visible == on) {
        return;
    }

    m_visible = on;
    emit visibleChanged(QPrivateSignal{});
}
