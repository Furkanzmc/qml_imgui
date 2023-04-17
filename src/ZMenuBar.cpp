#include "ZMenuBar.h"

#include "ZMenu.h"
#include "ZMenuItem.h"

#include <imgui.h>

ZMenuBar::ZMenuBar(QObject *parent)
    : ZWidget{parent}
{
}

QQmlListProperty<QObject> ZMenuBar::data()
{
    return QQmlListProperty<QObject>(
        this, nullptr,
        // Append
        [](QQmlListProperty<QObject> *prop, QObject *object) -> void {
            assert(prop);
            assert(object);
            auto *parent = qobject_cast<ZMenuBar *>(prop->object);
            assert(parent);
            if (auto *child = qobject_cast<ZWidget *>(object)) {
                parent->m_children.push_back(child);
            }

            parent->m_data.push_back(object);
        },
        // Count
        [](QQmlListProperty<QObject> *prop) -> qsizetype {
            assert(prop);
            auto *parent = static_cast<ZMenuBar *>(prop->object);
            assert(parent);
            return parent->m_data.size();
        },
        // At
        [](QQmlListProperty<QObject> *prop, qsizetype i) -> QObject * {
            assert(prop);
            auto *parent = static_cast<ZMenuBar *>(prop->object);
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

bool ZMenuBar::update()
{
    if (ImGui::BeginMenuBar()) {
        for (auto *item : m_children) {
            if (auto *menu = qobject_cast<ZMenu *>(item)) {
                menu->update();
            } else if (auto *menuItem = qobject_cast<ZMenuItem *>(item)) {
                menuItem->update();
            }
        }

        ImGui::EndMenuBar();
    }

    return true;
}
