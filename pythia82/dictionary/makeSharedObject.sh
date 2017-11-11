#!/bin/bash

set -x

# PYTHIA82 is a user-defined env variable for the PYTHIA 8.2 installation path
g++ dict4RootDct.cc ${PYTHIA82}/lib/libpythia8.a -o dict4Root.so -w -I${ROOTSYS}/include -shared -I${PYTHIA82}/include -O2 -ansi -pedantic -W -Wall -Wshadow -fPIC -Wl,-rpath,${PYTHIA82}/lib -ldl `root-config --cflags`
