#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./photon/photonJetAna.exe"

eventFileBase="./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
#eventFileBase="./out/events/photon/pythiaGenerateAndWrite_promptPhoton_noMPI_ISR_FSR.root"
#eventFileBase="./out/events/photon/pythiaGenerateAndWrite_promptPhoton_pthatMax60.root"
eventFiles=(
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
$eventFileBase
);

jetFileBase="./out/jets/photon/pythiaClusterJets_promptPhoton.root"
#jetFileBase="./out/jets/photon/pythiaClusterJets_promptPhoton_noMPI_ISR_FSR.root"
#jetFileBase="./out/jets/photon/pythiaClusterJets_promptPhoton_pthatMax60.root"
jetFiles=(
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
$jetFileBase
);

jetTrees=(
"ak3jets"
"ak3jetsCh"
"ak3jetsParton"
"ak3jetsPartonHard"
"ak3jetsSmeared"
"ak4jets"
"ak4jetsCh"
"ak4jetsParton"
"ak4jetsPartonHard"
"ak4jetsSmeared"
"ak5jets"
"ak7jets"
"ak8jets"
"ak8jetsParton"
"ak8jetsPartonHard"
);

outputFileBase="./out/analysis/photon/photonJetAna_promptPhoton"
#outputFileBase="./out/analysis/photon/photonJetAna_promptPhoton_noMPI_ISR_FSR"
#outputFileBase="./out/analysis/photon/photonJetAna_promptPhoton_pthatMax60"
outputFiles=(
$outputFileBase"_ak3jets.root"
$outputFileBase"_ak3jetsCh.root"
$outputFileBase"_ak3jetsParton.root"
$outputFileBase"_ak3jetsPartonHard.root"
$outputFileBase"_ak3jetsSmeared.root"
$outputFileBase"_ak4jets.root"
$outputFileBase"_ak4jetsCh.root"
$outputFileBase"_ak4jetsParton.root"
$outputFileBase"_ak4jetsPartonHard.root"
$outputFileBase"_ak4jetsSmeared.root"
$outputFileBase"_ak5jets.root"
$outputFileBase"_ak7jets.root"
$outputFileBase"_ak8jets.root"
$outputFileBase"_ak8jetsParton.root"
$outputFileBase"_ak8jetsPartonHard.root"
);

photonType=1

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    eventFile=${eventFiles[i1]}
    jetFile=${jetFiles[i1]}
    jetTree=${jetTrees[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $runCmd $progPath $eventFile $jetFile $jetTree $outputFile $photonType &> $outputFileLOG &
    echo "$runCmd $progPath $eventFile $jetFile $jetTree $outputFile $photonType &> $outputFileLOG &"
    wait
done


