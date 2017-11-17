#!/bin/bash

progPaths=(
"./pythiaClusterJets.exe"
);

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/pythiaClusterJets_promptPhoton.root"
);

jetRadii=(
"3"
);

minJetPts=(
"10"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    progPath=${progPaths[i1]}
    inputFile=${inputFiles[i1]}
    outputFile=${outputFiles[i1]}
    jetRadius=${jetRadii[i1]}
    minJetPt=${minJetPts[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $inputFile $outputFile $jetRadius $minJetPt &> $outputFileLOG &
    echo "$progPath $inputFile $outputFile $jetRadius $minJetPt &> $outputFileLOG &"
done


