CXX = g++
CXXFLAGS += -Wall -Werror -Wextra -O2 # -ansi -pedantic -W -Wshadow -fPIC -ldl
EXTRAFLAGS := -lTMVA -lRooFitCore -lRooFit

ROOT_BIN=$(ROOTSYS)/bin/
ROOT_INCLUDE=$(ROOTSYS)/include
ROOT_LIB=$(ROOTSYS)/lib

GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
	CXXFLAGS += -Wno-error=misleading-indentation
endif

.PHONY: all clean

all:
	@echo "Usage: make myProg.exe"

%.exe: %.cc
	$(CXX) $^ -o $@ -w $(CXXFLAGS) \
       -I$(ROOT_INCLUDE) `$(ROOTBIN)root-config --cflags` -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)root-config --glibs` \
        $(EXTRAFLAGS)

clean:
	rm *.exe || true

