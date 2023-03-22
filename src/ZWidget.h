#ifndef ZWIDGET_H
#define ZWIDGET_H

#include <QObject>

class ZWidget : public QObject
{
    Q_OBJECT

public:
    explicit ZWidget(QObject *parent = nullptr);
    virtual bool update() = 0;
};

#endif
