QMAKE_CXX         = /opt/mirror/llvm/bin/clang++
QMAKE_CXXFLAGS   += -std=c++2a \
					-freflection \
					-pedantic \
					-Wall \
					-Weverything \
					-Werror \
					-Wno-language-extension-token \
					-Wno-c++98-compat \
					-Wno-c++98-compat-pedantic \
					-Wno-c++20-compat \
					-Wno-c++2a-extensions \
					-Wno-padded \
					-Wno-weak-vtables \
					-Wno-global-constructors \
					-Wno-exit-time-destructors \
					-Wno-extra-semi-stmt \
					-Wno-redundant-parens \
					-Wno-documentation-unknown-command

TEMPLATE          = app
QT               += core quick

TARGET            = qt_factory

INCLUDEPATH      += /opt/mirror/llvm/include \
					../../../include \
					include

SOURCES          += src/Backend.cpp \
					src/BuilderViewModel.cpp \
					src/FactoryViewModel.cpp \
					src/ConstructorViewModel.cpp \
					src/ParameterViewModel.cpp \
					main.cpp

HEADERS          += include/Backend.hpp \
					include/BuilderViewModel.hpp \
					include/FactoryViewModel.hpp \
					include/ConstructorViewModel.hpp \
					include/ParameterViewModel.hpp

RESOURCES        += qt_factory.qrc
