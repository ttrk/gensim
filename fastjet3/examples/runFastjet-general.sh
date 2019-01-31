#!/bin/bash

set -x
fastjet3bin=$FASTJET3"/bin"
progExe="./fastjet-general.exe"
progCode="${progExe/.exe/.cc}"

g++ $progCode -o $progExe $(root-config --cflags --libs) `${fastjet3bin}/fastjet-config --cxxflags --libs --plugins` || exit 1

set +x

inputCards=(
"input1.txt"
"input2.txt"
"input3.txt"
"input4_E_scheme.txt"
"input4_WTA_pt_scheme.txt"
);

arrayIndices=${!inputCards[*]}
for i1 in $arrayIndices
do
  inputCard=${inputCards[i1]}
  suffix="${inputCard/input/}"
  suffix="${suffix/.txt/}"
  progOutput="${progExe/.exe/_card${suffix}.log}"
  $progExe $inputCard &> $progOutput &
  echo "$progExe $inputCard &> $progOutput &"
done

