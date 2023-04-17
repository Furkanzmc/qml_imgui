#ifndef ZAPPLICATION_WINDOW_H
#define ZAPPLICATION_WINDOW_H

#include <QTimer>

#include "ZWindow.h"

class GLFWwindow;

class ZApplicationWindow : public ZWindow
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ApplicationWindow)

public:
    explicit ZApplicationWindow(QObject *parent = nullptr);
    ~ZApplicationWindow();

    void componentComplete() override;

    bool update() final;

private:
    GLFWwindow *m_window{nullptr};
    QTimer m_timer{};
};

#endif
