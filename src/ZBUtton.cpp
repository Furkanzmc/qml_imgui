#include "ZButton.h"

#include <imgui.h>

ZButton::ZButton(QObject *parent)
    : ZWidget{parent}
{
}

QString ZButton::text() const
{
    return m_text;
}

void ZButton::setText(const QString &txt)
{
    if (m_text == txt) {
        return;
    }

    m_text = txt;
    emit textChanged(QPrivateSignal{});
}

bool ZButton::update()
{
    if (ImGui::Button(m_text.toUtf8().constData())) {
        emit clicked(QPrivateSignal{});
    }

    return true;
}
