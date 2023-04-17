#include "ZMenu.h"

#include "ZMenuItem.h"

#include <imgui.h>

ZMenu::ZMenu(QObject *parent)
    : ZWidget{parent}
{
}

QQmlListProperty<QObject> ZMenu::data()
{
    return QQmlListProperty<QObject>(
        this, nullptr,
        // Append
        [](QQmlListProperty<QObject> *prop, QObject *object) -> void {
            assert(prop);
            assert(object);
            auto *parent = qobject_cast<ZMenu *>(prop->object);
            assert(parent);
            if (auto *child = qobject_cast<ZWidget *>(object)) {
                parent->m_children.push_back(child);
            }

            parent->m_data.push_back(object);
        },
        // Count
        [](QQmlListProperty<QObject> *prop) -> qsizetype {
            assert(prop);
            auto *parent = static_cast<ZMenu *>(prop->object);
            assert(parent);
            return parent->m_data.size();
        },
        // At
        [](QQmlListProperty<QObject> *prop, qsizetype i) -> QObject * {
            assert(prop);
            auto *parent = static_cast<ZMenu *>(prop->object);
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

QString ZMenu::title() const
{
    return m_title;
}

void ZMenu::setTitle(const QString &txt)
{
    if (m_title == txt) {
        return;
    }

    m_title = txt;
    emit titleChanged(QPrivateSignal{});
}

bool ZMenu::update()
{
    if (ImGui::BeginMenu(m_title.toUtf8().constData())) {
        for (auto *item : m_children) {
            if (auto *menu = qobject_cast<ZMenu *>(item)) {
                menu->update();
            } else if (auto *menuItem = qobject_cast<ZMenuItem *>(item)) {
                menuItem->update();
            }
        }

        ImGui::EndMenu();
    }

    return true;
}
