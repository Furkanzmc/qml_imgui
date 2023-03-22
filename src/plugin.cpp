#include <QQmlApplicationEngine>
#include <QtQml/QQmlEngineExtensionPlugin>

extern void qml_register_types_Qml_ImGui();
Q_GHS_KEEP_REFERENCE(qml_register_types_Qml_ImGui);

class QmlImGuiPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

public:
    QmlImGuiPlugin(QObject *parent = nullptr)
        : QQmlEngineExtensionPlugin{parent}
    {
        volatile auto registration = &qml_register_types_Qml_ImGui;
        Q_UNUSED(registration);
    }
};

#include "plugin.moc"
