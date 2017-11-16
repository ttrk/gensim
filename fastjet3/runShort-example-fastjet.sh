#!/bin/bash

set -x
fastjet3bin=$FASTJET3"/bin"
g++ short-example-fastjet.cc -o short-example-fastjet.exe `${fastjet3bin}/fastjet-config --cxxflags --libs --plugins` || exit 1 

./short-example-fastjet.exe &> ./short-example-fastjet.log &
