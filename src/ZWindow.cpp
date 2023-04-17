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
            if (auto *child = qobject_cast<ZWidget *>(object)) {
                parent->m_children.push_back(child);
            }

            parent->m_data.push_back(object);
        },
        // Count
        [](QQmlListProperty<QObject> *prop) -> qsizetype {
            assert(prop);
            auto *parent = static_cast<ZWindow *>(prop->object);
            assert(parent);
            return parent->m_data.size();
        },
        // At
        [](QQmlListProperty<QObject> *prop, qsizetype i) -> QObject * {
            assert(prop);
            auto *parent = static_cast<ZWindow *>(prop->object);
            assert(parent);
            if (i >= parent->m_data.size()) {
                return nullptr;
            }

            return parent->m_data.at(i);
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
    if (!visible()) {
        return false;
    }

    ImGui::Begin(m_title.toUtf8().constData());
    for (auto *child : m_children) {
        child->update();
    }
    ImGui::End();

    return true;
}

void ZWindow::removeChild(QObject *obj)
{
    assert(obj);
    if (auto *child = qobject_cast<ZWidget *>(obj)) {
        auto foundIt = std::find(m_children.cbegin(), m_children.cend(), child);
        assert(foundIt != m_children.cend());
        m_children.erase(foundIt);
    }

    auto foundIt = std::find(m_data.cbegin(), m_data.cend(), obj);
    assert(foundIt != m_data.cend());
    m_data.erase(foundIt);
}

void ZWindow::addChild(QObject *obj)
{
    assert(obj);
    if (auto *child = qobject_cast<ZWidget *>(obj)) {
        assert(std::find(m_children.cbegin(), m_children.cend(), child) ==
               m_children.cend());
        m_children.push_back(child);
    }

    assert(std::find(m_data.cbegin(), m_data.cend(), obj) == m_data.cend());
    m_data.push_back(obj);
}

bool ZWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Type::Paint) {
        update();
    }

    return QObject::event(event);
}

void ZWindow::close()
{
    emit closed(QPrivateSignal{});
}

std::vector<ZWidget *> ZWindow::children() const
{
    return m_children;
}
