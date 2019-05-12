#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./sampleToyEvents.exe"

mode=1
nEvents=500
maxEta=2.6
meanPt=0.65
minPt=0
partTreeName="evtToy"
rndSeedParticle=6789

minMultCh=239
maxMultCh=261
mindNdEta=47
maxdNdEta=53
outputFiles=(
"./sampleToyEvents_PLACEHOLDER_N"$nEvents".root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    outputFile=${outputFiles[i1]}
    outputFile="${outputFile/PLACEHOLDER/minMultCh${minMultCh}_maxMultCh${maxMultCh}}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $mode $outputFile $nEvents --minMultCh=$minMultCh --maxMultCh=$maxMultCh --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --minMultCh=$minMultCh --maxMultCh=$maxMultCh --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &"

    outputFile=${outputFiles[i1]}
    outputFile="${outputFile/PLACEHOLDER/mindNdEta${mindNdEta}_maxdNdEta${maxdNdEta}}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $mode $outputFile $nEvents --mindNdEta=$mindNdEta --maxdNdEta=$maxdNdEta --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --mindNdEta=$mindNdEta --maxdNdEta=$maxdNdEta --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &"

    wait
done

