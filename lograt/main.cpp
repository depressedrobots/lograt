#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>

#include "loglinesmodel.h"
#include "columnconfig.h"

int main(int argc, char *argv[])
{
    if( argc > 2 )
    {
        qDebug() << "usage: lograt [FILENAME]";
        return 1;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<LogLinesModel>("lograt", 1, 0, "LogLinesModel");
    qmlRegisterType<ColumnConfig>("lograt", 1, 0, "ColumnConfig");

    QQmlApplicationEngine engine;
    auto ctx = engine.rootContext();
    const auto filename = argc == 2 ? QString{argv[1]} : QString{};
    ctx->setContextProperty("filename", filename);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
