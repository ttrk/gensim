#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./pythiaGenerateAndWrite.exe"

progCards=(
"./cards/photon/promptPhoton.cmnd"
"./cards/photon/promptPhoton_off_MPI_ISR_FSR_BR.cmnd"
"./cards/photon/promptPhoton_off_MPI_ISR_FSR_BR_pthatBias.cmnd"
);

outputFiles=(
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton_off_MPI_ISR_FSR_BR.root"
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton_off_MPI_ISR_FSR_BR_pthatBias.root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    progCard=${progCards[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $runCmd $progPath $progCard $outputFile &> $outputFileLOG &
    echo "$runCmd $progPath $progCard $outputFile &> $outputFileLOG &"
done


