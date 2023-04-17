#ifndef ZMENU_H
#define ZMENU_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZMenu : public ZWidget
{
    Q_OBJECT

    QML_NAMED_ELEMENT(Menu)
    Q_CLASSINFO("DefaultProperty", "data")

    Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    ZMenu(QObject *parent = nullptr);

    QQmlListProperty<QObject> data();

    QString title() const;
    void setTitle(const QString &txt);

    bool update() final;

signals:
    void titleChanged(QPrivateSignal);
    void clicked(QPrivateSignal);

private:
    std::vector<ZWidget *> m_children;
    std::vector<QObject *> m_data;
    QString m_title{};
};

#endif
