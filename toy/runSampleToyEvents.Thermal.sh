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

multCh=247
dNdEta=52
outputFiles=(
"./sampleToyEvents_PLACEHOLDER_N"$nEvents".root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    outputFile=${outputFiles[i1]}
    outputFile="${outputFile/PLACEHOLDER/multCh${multCh}}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $mode $outputFile $nEvents --multCh=$multCh --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --multCh=$multCh --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &"

    outputFile=${outputFiles[i1]}
    outputFile="${outputFile/PLACEHOLDER/dNdEta${dNdEta}}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $mode $outputFile $nEvents --dNdEta=$dNdEta --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --dNdEta=$dNdEta --maxEta=$maxEta --meanPt=$meanPt --minPt=$minPt --rndSeedParticle=$rndSeedParticle --particleTree=$partTreeName &> $outputFileLOG &"

    wait
done

