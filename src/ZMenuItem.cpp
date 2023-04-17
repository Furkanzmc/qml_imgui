#include "ZMenuItem.h"

#include <imgui.h>

ZMenuItem::ZMenuItem(QObject *parent)
    : ZWidget{parent}
{
}

QString ZMenuItem::text() const
{
    return m_text;
}

void ZMenuItem::setText(const QString &txt)
{
    if (m_text == txt) {
        return;
    }

    m_text = txt;
    emit textChanged(QPrivateSignal{});
}

bool ZMenuItem::update()
{
    if (ImGui::MenuItem(m_text.toUtf8().constData())) {
        emit clicked(QPrivateSignal{});
    }

    return true;
}
