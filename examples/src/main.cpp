#include <QCoreApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app{argc, argv};

    QDir pluginDir{argv[0]};
    pluginDir.cdUp();
    pluginDir.cdUp();
    pluginDir.cd("qml/");

    QQmlApplicationEngine engine;
    engine.setPluginPathList({pluginDir.absolutePath(), "."});

    qDebug() << "cpp: pluginPathList:" << engine.pluginPathList();

    const QUrl url{"qrc:/qml/main.qml"};

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
    engine.load(url);

    int return_code = app.exec();

    return return_code;
}
