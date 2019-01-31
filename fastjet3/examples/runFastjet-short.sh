#!/bin/bash

set -x
fastjet3bin=$FASTJET3"/bin"
g++ fastjet-short.cc -o fastjet-short.exe `${fastjet3bin}/fastjet-config --cxxflags --libs --plugins` || exit 1 

./fastjet-short.exe &> ./fastjet-short.log &
