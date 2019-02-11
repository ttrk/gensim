#!/bin/bash

progPath="./pythiaClusterJets.exe"

inputFileBase="./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
inputFiles=(
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
$inputFileBase
);

outputFileBase="./out/jets/photon/pythiaClusterJets_promptPhoton.root"
outputFiles=(
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
$outputFileBase
);

jetRadii=(
"3"
"3"
"3"
"3"
"4"
"4"
"4"
"4"
"5"
"7"
"8"
"8"
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
"5"
"5"
"5"
"5"
);

constituentTypes=(
"0"
"1"
"2"
"3"
"0"
"1"
"2"
"3"
"0"
"0"
"0"
"2"
"3"
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


