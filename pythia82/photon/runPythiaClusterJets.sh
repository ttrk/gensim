#!/bin/bash

progPath="./pythiaClusterJets.exe"

inputFiles=(
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
"./photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
"./photon/pythiaClusterJets_promptPhoton.root"
);

jetRadii=(
"3"
"3"
"3"
"4"
"4"
"4"
"5"
"7"
"8"
);

minJetPts=(
"5"
"5"
"5"
"5"
"5"
"5"
"5"
"5"
"5"
);

constituentTypes=(
"0"
"1"
"2"
"0"
"1"
"2"
"0"
"0"
"0"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    inputFile=${inputFiles[i1]}
    outputFile=${outputFiles[i1]}
    jetRadius=${jetRadii[i1]}
    minJetPt=${minJetPts[i1]}
    constituentType=${constituentTypes[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $progPath $inputFile $outputFile $jetRadius $minJetPt $constituentType &> $outputFileLOG &
    echo "$progPath $inputFile $outputFile $jetRadius $minJetPt $constituentType &> $outputFileLOG &"
    wait
done


