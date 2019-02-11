#!/bin/bash

progPath="./pythiaGenerateAndWrite.exe"

progCards=(
"./cards/photon/promptPhoton.cmnd"
);

outputFiles=(
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    progCard=${progCards[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $progCard $outputFile &> $outputFileLOG &
    echo "$progPath $progCard $outputFile &> $outputFileLOG &"
done

