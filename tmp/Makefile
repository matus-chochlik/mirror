PREFIX?=/opt/llvm/bin
CXX=$(PREFIX)/clang++
CXXFLAGS= -std=c++17 -Xclang -freflection -fsyntax-only

all: test

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


