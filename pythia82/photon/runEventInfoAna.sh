#!/bin/bash

progPath="./eventInfoAna.exe"

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/eventInfoAna_promptPhoton.root"
);

processCodes=("-1" "201" "202,203")
processCodesSuffixes=("" "_proc201" "_proc202203")

arrayIndices=${!outputFiles[*]}
indicesProcessCodes=${!processCodes[*]}
for i1 in $arrayIndices
do
  for i2 in $indicesProcessCodes
  do
    inputFile=${inputFiles[i1]}

    processCode=${processCodes[i2]}
    processCodeSuffix=${processCodesSuffixes[i2]}

    outputFileTmp=${outputFiles[i1]}
    outputFile="${outputFileTmp/.root/${processCodeSuffix}.root}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $inputFile $outputFile $processCode &> $outputFileLOG &
    echo "$progPath $inputFile $outputFile $processCode &> $outputFileLOG &"
  done
done


