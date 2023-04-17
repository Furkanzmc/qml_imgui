#include "ZText.h"

#include <imgui.h>

ZText::ZText(QObject *parent)
    : ZWidget{parent}
{
}

QString ZText::text() const
{
    return m_text;
}

void ZText::setText(const QString &txt)
{
    if (m_text == txt) {
        return;
    }

    m_text = txt;
    emit textChanged(QPrivateSignal{});
}

bool ZText::update()
{
    ImGui::Text("%s", m_text.toUtf8().constData());

    return true;
}
