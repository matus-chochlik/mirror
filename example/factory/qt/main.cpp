/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "Backend.hpp"
#include "BuilderViewModel.hpp"
#include "ConstructorViewModel.hpp"
#include "FactoryViewModel.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<BuilderViewModel>(
      "com.github.matus-chochlik", 1, 0, "BuilderViewModel");
    qmlRegisterType<FactoryViewModel>(
      "com.github.matus-chochlik", 1, 0, "FactoryViewModel");
    qmlRegisterType<ConstructorViewModel>(
      "com.github.matus-chochlik", 1, 0, "ConstructorViewModel");

    Backend backend;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.load("qrc:///main.qml");

    return app.exec();
}
