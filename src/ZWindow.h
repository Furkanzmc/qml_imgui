#ifndef ZWINDOW_H
#define ZWINDOW_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZWindow : public ZWidget
{
    Q_OBJECT

    Q_CLASSINFO("DefaultProperty", "data")

    QML_NAMED_ELEMENT(Window)

    Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    ZWindow(QObject *parent = nullptr);

    QQmlListProperty<QObject> data();

    QString title() const;
    void setTitle(const QString &txt);

    bool update() override;

    bool event(QEvent *event) final;

protected:
    std::vector<ZWidget*> children() const;

signals:
    void titleChanged(QPrivateSignal);

private:
    QString m_title;
    std::vector<ZWidget *> m_children;
};

#endif
