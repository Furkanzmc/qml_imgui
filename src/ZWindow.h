#ifndef ZWINDOW_H
#define ZWINDOW_H

#include "ZWidget.h"

#include <imgui.h>

#include <qqml.h>
#include <QString>

class ZWindow : public ZWidget
{
    Q_OBJECT

    Q_CLASSINFO("DefaultProperty", "data")

    QML_NAMED_ELEMENT(Window)

    Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(WindowFlags flags READ flags WRITE setFlags NOTIFY flagsChanged)

public:
    enum class WindowFlag
    {
        None = ImGuiWindowFlags_None,
        NoTitleBar = ImGuiWindowFlags_NoTitleBar,
        NoResize = ImGuiWindowFlags_NoResize,
        NoMove = ImGuiWindowFlags_NoMove,
        NoScrollbar = ImGuiWindowFlags_NoScrollbar,
        NoScrollWithMouse = ImGuiWindowFlags_NoScrollWithMouse,
        NoCollapse = ImGuiWindowFlags_NoCollapse,
        AlwaysAutoResize = ImGuiWindowFlags_AlwaysAutoResize,
        NoBackground = ImGuiWindowFlags_NoBackground,
        NoSavedSettings = ImGuiWindowFlags_NoSavedSettings,
        NoMouseInputs = ImGuiWindowFlags_NoMouseInputs,
        MenuBar = ImGuiWindowFlags_MenuBar,
        HorizontalScrollbar = ImGuiWindowFlags_HorizontalScrollbar,
        NoFocusOnAppearing = ImGuiWindowFlags_NoFocusOnAppearing,
        NoBringToFrontOnFocus = ImGuiWindowFlags_NoBringToFrontOnFocus,
        AlwaysVerticalScrollbar = ImGuiWindowFlags_AlwaysVerticalScrollbar,
        AlwaysHorizontalScrollbar = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
        AlwaysUseWindowPadding = ImGuiWindowFlags_AlwaysUseWindowPadding,
        NoNavInputs = ImGuiWindowFlags_NoNavInputs,
        NoNavFocus = ImGuiWindowFlags_NoNavFocus,
        UnsavedDocument = ImGuiWindowFlags_UnsavedDocument,
        NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
        NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
        NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs |
            ImGuiWindowFlags_NoNavFocus,
    };
    Q_ENUM(WindowFlag);
    Q_DECLARE_FLAGS(WindowFlags, WindowFlag)
    Q_FLAGS(WindowFlags)

public:
    ZWindow(QObject *parent = nullptr);

    QQmlListProperty<QObject> data();

    QString title() const;
    void setTitle(const QString &txt);

    WindowFlags flags() const;
    void setFlags(WindowFlags fls);

    bool update() override;
    void removeChild(QObject *obj) final;
    void addChild(QObject *obj) final;

    bool event(QEvent *event) final;
    Q_INVOKABLE void close();

protected:
    std::vector<ZWidget *> children() const;

signals:
    void titleChanged(QPrivateSignal);
    void closed(QPrivateSignal);
    void flagsChanged(QPrivateSignal);

private:
    QString m_title;
    std::vector<ZWidget *> m_children;
    std::vector<QObject *> m_data;
    WindowFlags m_windowFlags{WindowFlag::None};
};

#endif
