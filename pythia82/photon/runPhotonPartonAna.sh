#!/bin/bash

progPaths=(
"./photon/photonPartonAna.exe"
);

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/photonPartonAna_promptPhoton.root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    progPath=${progPaths[i1]}
    inputFile=${inputFiles[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $inputFile $outputFile &> $outputFileLOG &
    echo "$progPath $inputFile $outputFile &> $outputFileLOG &"
done


