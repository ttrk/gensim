CXX = g++
CXXFLAGS += -Wall -Werror -Wextra -O2
ROOTFLAGS := `root-config --cflags --libs`
EXTRAFLAGS := -lTMVA -lRooFitCore -lRooFit

GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
	CXXFLAGS += -Wno-error=misleading-indentation
endif

SRCS = $(wildcard */*.cc)
SRCS += $(wildcard */*/*.cc)
EXES = $(patsubst %.cc,%.exe,$(SRCS))

# FASTJET3 configuration.
# FASTJET3 is a user-defined env variable for the FASTJET 3 installation path
FASTJET3_USE=true
FASTJET3_BIN=$(FASTJET3)/bin
FASTJET3_INCLUDE=$(FASTJET3)/include
FASTJET3_LIB=$(FASTJET3)/lib
FASTJET3FLAGS := -I$(FASTJET3_INCLUDE) -L$(FASTJET3_LIB) -Wl,-rpath,$(FASTJET3_LIB) -lfastjet

.PHONY: all clean

all: $(EXES)

%.exe: %.cc
	$(CXX) $< $(CXXFLAGS) $(ROOTFLAGS) $(EXTRAFLAGS) $(FASTJET3FLAGS) -o $@

clean:
	@$(EXES)

