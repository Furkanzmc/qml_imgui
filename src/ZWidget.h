#ifndef ZWIDGET_H
#define ZWIDGET_H

#include <QObject>
#include <QQmlParserStatus>

class QEvent;

class ZWidget : public QObject, public QQmlParserStatus
{
    Q_OBJECT

    Q_CLASSINFO("ParentProperty", "parentItem")
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QObject *parent READ parent NOTIFY parentChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit ZWidget(QObject *parent = nullptr);

    virtual bool update() = 0;
    virtual void removeChild(QObject *obj){};
    virtual void addChild(QObject *obj){};

    void classBegin() final
    {
    }
    void componentComplete() override
    {
    }

    void childEvent(QChildEvent *event) override;

    bool visible() const;
    void setVisible(bool on);

signals:
    void parentChanged(QPrivateSignal);
    void visibleChanged(QPrivateSignal);

private:
    bool m_visible{true};
};

#endif
