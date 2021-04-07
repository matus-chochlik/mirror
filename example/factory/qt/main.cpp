/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "Backend.hpp"
#include "BuilderViewModel.hpp"
#include "ConstructorViewModel.hpp"
#include "FactoryViewModel.hpp"
#include "ParameterViewModel.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<BuilderViewModel>(
      "com.github.matus-chochlik", 1, 0, "BuilderViewModel", {});
    qmlRegisterUncreatableType<FactoryViewModel>(
      "com.github.matus-chochlik", 1, 0, "FactoryViewModel", {});
    qmlRegisterUncreatableType<ConstructorViewModel>(
      "com.github.matus-chochlik", 1, 0, "ConstructorViewModel", {});
    qmlRegisterUncreatableType<ParameterViewModel>(
      "com.github.matus-chochlik", 1, 0, "ParameterViewModel", {});

    Backend backend;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.load("qrc:///main.qml");

    return app.exec();
}
