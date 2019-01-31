#!/bin/bash

set -x
fastjet3bin=$FASTJET3"/bin"
progExe="./fastjet-general.exe"
progCode="${progExe/.exe/.cc}"

g++ $progCode -o $progExe $(root-config --cflags --libs) `${fastjet3bin}/fastjet-config --cxxflags --libs --plugins` || exit 1

set +x

inputCards=(
"./input/card1.txt"
"./input/card2.txt"
"./input/card3.txt"
"./input/card4_E_scheme.txt"
"./input/card4_WTA_pt_scheme.txt"
);

arrayIndices=${!inputCards[*]}
for i1 in $arrayIndices
do
  inputCard=${inputCards[i1]}
  nameTmp=$(basename ${inputCard})
  nameTmp="${nameTmp/.txt/}"
  progOutput="./output/fastjet-general-"${nameTmp}".log"
  $progExe $inputCard &> $progOutput &
  echo "$progExe $inputCard &> $progOutput &"
done

