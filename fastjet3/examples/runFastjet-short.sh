#!/bin/bash

set -x
fastjet3bin=$FASTJET3"/bin"
progExe="./fastjet-short.exe"
progCode="${progExe/.exe/.cc}"

g++ $progCode -o $progExe `${fastjet3bin}/fastjet-config --cxxflags --libs --plugins` || exit 1

progOutput="${progExe/.exe/.log}"
$progExe &> $progOutput &
