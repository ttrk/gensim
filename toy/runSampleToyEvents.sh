#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./sampleToyEvents.exe"

inputFiles=(
"input/spectra_hiBinVSngen_etaVSpt_Hydjet_Quenched_Cymbal5Ev8_PbPbMinBias_5020GeV.root"
);

mode=0
nEvents=5000
minCent=0
maxCent=10
minPt=0
eventInfoTree="evtInfoToyHydjet"
partTreeName="evtToyHydjet"
rndSeedHiBin=12345
rndSeedParticle=6789

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

    $runCmd $progPath $mode $outputFile $nEvents --inputFile=$inputFile --minCent=$minCent --maxCent=$maxCent --minPt=$minPt --rndSeedCent=$rndSeedHiBin --rndSeedParticle=$rndSeedParticle --eventInfoTree=$eventInfoTree --particleTree=$partTreeName &> $outputFileLOG &
    echo "$runCmd $progPath $mode $outputFile $nEvents --inputFile=$inputFile --minCent=$minCent --maxCent=$maxCent --minPt=$minPt --rndSeedCent=$rndSeedHiBin --rndSeedParticle=$rndSeedParticle --eventInfoTree=$eventInfoTree --particleTree=$partTreeName &> $outputFileLOG &"
    wait
done

