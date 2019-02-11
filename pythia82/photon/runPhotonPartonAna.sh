#!/bin/bash

progPath="./photon/photonPartonAna.exe"

inputFiles=(
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./out/analysis/photon/photonPartonAna_promptPhoton.root"
);

photonStatuses=(0 1)
photonStatusesLabels=("phoHard" "phoOut")

partonStatuses=(0 1)
partonStatusesLabels=("qgHard" "qgOut")

arrayIndices=${!outputFiles[*]}
indicesPhotonStatuses=${!photonStatuses[*]}
indicesPartonStatuses=${!partonStatuses[*]}
for i1 in $arrayIndices
do
  for i2 in $indicesPhotonStatuses
  do
    for i3 in $indicesPartonStatuses
    do
      inputFile=${inputFiles[i1]}

      photonStatus=${photonStatuses[i2]}
      photonStatusLabel=${photonStatusesLabels[i2]}
      partonStatus=${partonStatuses[i3]}
      partonStatusLabel=${partonStatusesLabels[i3]}

      outputFileTmp=${outputFiles[i1]}
      outputFile="${outputFileTmp/.root/_${photonStatusLabel}_${partonStatusLabel}.root}"
      outputFileLOG="${outputFile/.root/.log}"
      outDir=$(dirname "${outputFile}")
      mkdir -p $outDir
      $progPath $inputFile $outputFile $photonStatus $partonStatus &> $outputFileLOG &
      echo "$progPath $inputFile $outputFile $photonStatus $partonStatus &> $outputFileLOG &"
    done
  done
done


