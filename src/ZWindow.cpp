#include "ZWindow.h"

#include <QEvent>

#include <imgui.h>

ZWindow::ZWindow(QObject *parent)
    : ZWidget{parent}
{
}

QQmlListProperty<QObject> ZWindow::data()
{
    return QQmlListProperty<QObject>(
        this, nullptr,
        // Append
        [](QQmlListProperty<QObject> *prop, QObject *object) -> void {
            assert(prop);
            assert(object);
            auto *parent = qobject_cast<ZWindow *>(prop->object);
            assert(parent);
            parent->m_children.push_back(qobject_cast<ZWidget *>(object));
        },
        // Count
        [](QQmlListProperty<QObject> *prop) -> qsizetype {
            assert(prop);
            auto *parent = static_cast<ZWindow *>(prop->object);
            assert(parent);
            return parent->m_children.size();
        },
        // At
        [](QQmlListProperty<QObject> *prop, qsizetype i) -> QObject * {
            assert(prop);
            auto *parent = static_cast<ZWindow *>(prop->object);
            assert(parent);
            if (i >= parent->m_children.size()) {
                return nullptr;
            }

            return parent->m_children.at(i);
        },
        // Clear
        [](QQmlListProperty<QObject> *prop) -> void {
            assert(prop);
        });
}

QString ZWindow::title() const
{
    return m_title;
}

void ZWindow::setTitle(const QString &txt)
{
    if (m_title == txt) {
        return;
    }

    m_title = txt;
    emit titleChanged(QPrivateSignal{});
}

bool ZWindow::update()
{
    ImGui::Begin(m_title.toUtf8().constData());
    for (auto *child : m_children) {
        child->update();
    }
    ImGui::End();

    return true;
}

bool ZWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Type::Paint) {
        update();
    }

    return QObject::event(event);
}

std::vector<ZWidget *> ZWindow::children() const
{
    return m_children;
}
