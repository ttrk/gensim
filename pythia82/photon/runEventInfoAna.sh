#!/bin/bash

progPath="./eventInfoAna.exe"

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/eventInfoAna_promptPhoton.root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
  inputFile=${inputFiles[i1]}

  outputFile=${outputFiles[i1]}
  outputFileLOG="${outputFile/.root/.log}"
  outDir=$(dirname "${outputFile}")
  mkdir -p $outDir
  $progPath $inputFile $outputFile &> $outputFileLOG &
  echo "$progPath $inputFile $outputFile &> $outputFileLOG &"
done


