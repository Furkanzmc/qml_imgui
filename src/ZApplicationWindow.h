#ifndef ZAPPLICATION_WINDOW_H
#define ZAPPLICATION_WINDOW_H

#include <QQmlParserStatus>
#include <QTimer>

#include "ZWindow.h"

class GLFWwindow;

class ZApplicationWindow : public ZWindow, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    QML_NAMED_ELEMENT(ApplicationWindow)

public:
    explicit ZApplicationWindow(QObject *parent = nullptr);
    ~ZApplicationWindow();

    void classBegin() final;
    void componentComplete() final;

    bool update() final;

private:
    GLFWwindow *m_window{nullptr};
    QTimer m_timer{};
};

#endif
