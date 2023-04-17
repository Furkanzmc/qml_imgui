#ifndef ZMENU_BAR_H
#define ZMENU_BAR_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZMenuBar : public ZWidget
{
    Q_OBJECT

    QML_NAMED_ELEMENT(MenuBar)
    Q_CLASSINFO("DefaultProperty", "data")

    Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)

public:
    ZMenuBar(QObject *parent = nullptr);

    QQmlListProperty<QObject> data();

    bool update() final;

signals:
    void textChanged(QPrivateSignal);
    void clicked(QPrivateSignal);

private:
    std::vector<ZWidget *> m_children;
    std::vector<QObject *> m_data;
};

#endif
