#ifndef ZTEXT_H
#define ZTEXT_H

#include "ZWidget.h"

#include <qqml.h>
#include <QString>

class ZText : public ZWidget
{
    Q_OBJECT

    QML_NAMED_ELEMENT(Text)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    ZText(QObject *parent = nullptr);

    QString text() const;
    void setText(const QString &txt);

    bool update() final;

signals:
    void textChanged(QPrivateSignal);

private:
    QString m_text;
};

#endif
