SHELL=/bin/bash
PREFIX?=/tmp/llvm/bin
CXX=$(PREFIX)/clang++
CXXFLAGS= -std=c++17 -Xclang -freflection -fsyntax-only

all: P0953.time P1240.time

.PRECIOUS: P0953_list.cxx P1240_list.cxx

%_list.cxx: %_head.cxx %_one.cxx
	cat $*_head.cxx > $@
	( for i in {0..10000}; do sed s,@,$$i,g $*_one.cxx; done ) >> $@

%.time: %_list.cxx
	time ( $(CXX) $(CXXFLAGS) $< )

clean:
	rm -f *_list.cxx
