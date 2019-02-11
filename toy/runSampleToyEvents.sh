#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./sampleToyEvents.exe"

inputFiles=(
"input/spectra_hiBinVSngen_etaVSpt_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV.root"
);

nEvents=10000
minCent=0
maxCent=10
minPt=0

outputFiles=(
"./sampleToyEvents_cent"$minCent$maxCent"_N"$nEvents".root"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    inputFile=${inputFiles[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $runCmd $progPath $inputFile $outputFile $nEvents $minCent $maxCent $minPt &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile $nEvents $minCent $maxCent $minPt &> $outputFileLOG &"
    wait
done

