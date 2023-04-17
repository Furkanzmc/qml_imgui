#ifndef ZBUTTON_H
#define ZBUTTON_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZButton : public ZWidget
{
    Q_OBJECT

    QML_NAMED_ELEMENT(Button)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    ZButton(QObject *parent = nullptr);

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
