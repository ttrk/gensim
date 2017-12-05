#!/bin/bash

progPath="./photon/photonPartonAna.exe"

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/photonPartonAna_promptPhoton.root"
);

photonStatuses=(0 1)
photonStatusesLabels=("phoHard" "phoOut")

arrayIndices=${!outputFiles[*]}
indicesPhotonStatuses=${!photonStatuses[*]}
for i1 in $arrayIndices
do
  for i2 in $indicesPhotonStatuses
  do
    inputFile=${inputFiles[i1]}

    photonStatus=${photonStatuses[i2]}
    photonStatusLabel=${photonStatusesLabels[i2]}

    outputFileTmp=${outputFiles[i1]}
    outputFile="${outputFileTmp/.root/_$photonStatusLabel.root}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $inputFile $outputFile $photonStatus &> $outputFileLOG &
    echo "$progPath $inputFile $outputFile $photonStatus &> $outputFileLOG &"
  done
done


