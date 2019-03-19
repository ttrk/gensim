#!/bin/bash

runCmd=$MYRUN
export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/

progPath="./analysis/qcdAna.exe"

## prompt photon
fileSuffix="promptPhoton"
defaultBosonType=3
defaultBosonTypeStr="outgoingMaxPhotonIso" # "outgoingHardPhoton"
defaultAnaType=0
defaultProcessType=0

eventFile="./out/events/photon/pythiaGenerateAndWrite_"$fileSuffix".root"
jetFile="./out/jets/photon/pythiaClusterJets_"$fileSuffix".root"
particleFile="NULL"
particleTree="NULL"
sigBkgType=0

jetTrees=(
"ak3jets"
"ak3jets"
"ak3jets"
"ak3jets"
##
"ak3jetsParton"
"ak3jetsSmeared"
"ak3jetsWTA"
"ak4jets"
"ak4jetsParton"
"ak4jetsSmeared"
"ak4jetsWTA"
"ak5jets"
"ak6jets"
"ak7jets"
"ak8jets"
);


outputFiles=(
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jets_hardPhoton.root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jets_outgoingHardPhoton.root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jets_outgoingMaxPhoton.root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jets_outgoingMaxPhotonIso.root"
##
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jetsParton_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jetsSmeared_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak3jetsWTA_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak4jets_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak4jetsParton_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak4jetsSmeared_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak4jetsWTA_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak5jets_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak6jets_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak7jets_"$defaultBosonTypeStr".root"
"./out/analysis/photon/qcdAna_"$fileSuffix"_ak8jets_"$defaultBosonTypeStr".root"
);

analysisTypes=(
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
##
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
$defaultAnaType
);


processTypes=(
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
##
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
$defaultProcessType
);

ewBosonTypes=(
0
1
2
3
##
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
$defaultBosonType
);


arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    jetTree=${jetTrees[i1]}
    analysisType=${analysisTypes[i1]}
    processType=${processTypes[i1]}
    ewBosonType=${ewBosonTypes[i1]}
    outputFile=${outputFiles[i1]}
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $eventFile $jetFile $jetTree $particleFile $particleTree $outputFile $analysisType $processType $sigBkgType $ewBosonType &> $outputFileLOG &
    echo "$runCmd $progPath $eventFile $jetFile $jetTree $particleFile $particleTree $outputFile $analysisType $processType $sigBkgType $ewBosonType &> $outputFileLOG &"
    wait
done


