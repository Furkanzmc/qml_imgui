#ifndef ZMENU_ITEM_H
#define ZMENU_ITEM_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZMenuItem : public ZWidget
{
    Q_OBJECT

    QML_NAMED_ELEMENT(MenuItem)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    ZMenuItem(QObject *parent = nullptr);

    QString text() const;
    void setText(const QString &txt);

    bool update() final;

signals:
    void textChanged(QPrivateSignal);
    void clicked(QPrivateSignal);

private:
    QString m_text;
};

#endif
