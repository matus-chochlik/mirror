QMAKE_CXX         = /opt/mirror/llvm/bin/clang++
QMAKE_CXXFLAGS   += -std=c++2b \
					-stdlib=libc++ \
					-freflection-ts \
					-freflection-ext \
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

QMAKE_LINK        = /opt/mirror/llvm/bin/clang++
QMAKE_LFLAGS     += -std=c++2b \
					-stdlib=libc++ \
					-Wl,-rpath,/opt/mirror/llvm/lib \
					-Wl,-rpath,/opt/mirror/llvm/lib/x86_64-unknown-linux-gnu

TEMPLATE          = app
QT               += core quick

TARGET            = qt_factory

INCLUDEPATH      += ../../../../include \
					include

SOURCES          += src/Backend.cpp \
					src/BuilderViewModel.cpp \
					src/FactoryViewModel.cpp \
					src/ConstructorViewModel.cpp \
					src/ParameterViewModel.cpp \
					src/AtomicViewModel.cpp \
					main.cpp

HEADERS          += include/Backend.hpp \
					include/BuilderViewModel.hpp \
					include/FactoryViewModel.hpp \
					include/ConstructorViewModel.hpp \
					include/ParameterViewModel.hpp \
					include/AtomicViewModel.hpp

RESOURCES        += qt_factory.qrc
