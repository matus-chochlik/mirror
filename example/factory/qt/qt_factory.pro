TEMPLATE      = app
CONFIG       += c++17
QT           += core quick

TARGET        = qt_factory

INCLUDEPATH  += include
SOURCES      += src/Backend.cpp \
				src/BuilderViewModel.cpp \
				src/FactoryViewModel.cpp \
				src/ConstructorViewModel.cpp \
				main.cpp
HEADERS      += include/Backend.hpp \
				include/BuilderViewModel.hpp \
				include/FactoryViewModel.hpp \
				include/ConstructorViewModel.hpp
RESOURCES    += qt_factory.qrc
