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
    void removeChild(QObject *obj) final;
    void addChild(QObject *obj) final;

    bool event(QEvent *event) final;
    Q_INVOKABLE void close();

protected:
    std::vector<ZWidget *> children() const;

signals:
    void titleChanged(QPrivateSignal);
    void closed(QPrivateSignal);

private:
    QString m_title;
    std::vector<ZWidget *> m_children;
    std::vector<QObject *> m_data;
};

#endif
