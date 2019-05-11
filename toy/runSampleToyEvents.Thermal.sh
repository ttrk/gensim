#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./sampleToyEvents.exe"

mode=1
nEvents=5000
multCh=89
meanPt=0.65
minPt=0
partTreeName="evtToy"
rndSeedParticle=6789

outputFiles=(
"./sampleToyEvents_multCh"$multCh"_N"$nEvents".root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $mode $outputFile $nEvents --multCh=$multCh --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --multCh=$multCh --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &"
    wait
done

