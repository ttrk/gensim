#!/bin/bash

runCmd=$MYRUN
export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/

progPath="./analysis/qcdAna.exe"

## prompt photon
fileSuffix="hardQCD"
defaultBosonType=-999
defaultAnaType=1
defaultAnaTypeStr="leadjet"
defaultProcessType=0

eventFile="./out/events/qcd/pythiaGenerateAndWrite_"$fileSuffix".root"
jetFile="./out/jets/qcd/pythiaClusterJets_"$fileSuffix".root"
particleFile="NULL"
particleTree="NULL"
sigBkgType=0

jetTrees=(
"ak3jets"
"ak3jetsParton"
"ak3jetsSmeared"
"ak4jetsParton"
"ak4jetsSmeared"
"ak4jets"
"ak5jets"
"ak7jets"
"ak8jets"
##
"ak3jets"
"ak3jets"
## dijet
"ak3jets"
## inclusive jet
"ak3jets"
);


outputFiles=(
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak3jets.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak3jetsParton.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak3jetsSmeared.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak4jetsParton.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak4jetsSmeared.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak4jets.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak5jets.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak7jets.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_ak8jets.root"
##
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_x2qg_ak3jets.root"
"./out/analysis/qcd/qcdAna_"$fileSuffix"_"$defaultAnaTypeStr"_x2gg_ak3jets.root"
## dijet
"./out/analysis/qcd/qcdAna_"$fileSuffix"_dijet_ak3jets.root"
## inclusive jet
"./out/analysis/qcd/qcdAna_"$fileSuffix"_inclusivejet_ak3jets.root"
);

analysisTypes=(
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
##
$defaultAnaType
$defaultAnaType
## dijet
2
## inclusive jet
3
);


processTypes=(
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
##
1001
1002
## dijet
$defaultProcessType
## inclusive jet
$defaultProcessType
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    jetTree=${jetTrees[i1]}
    analysisType=${analysisTypes[i1]}
    processType=${processTypes[i1]}
    ewBosonType=${defaultBosonType}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $eventFile $jetFile $jetTree $particleFile $particleTree $outputFile $analysisType $processType $sigBkgType $ewBosonType &> $outputFileLOG &
    echo "$runCmd $progPath $eventFile $jetFile $jetTree $particleFile $particleTree $outputFile $analysisType $processType $sigBkgType $ewBosonType &> $outputFileLOG &"
    wait
done


