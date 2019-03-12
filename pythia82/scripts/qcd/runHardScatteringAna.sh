#!/bin/bash

runCmd=$MYRUN
export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/

progPath="./analysis/hardScatteringAna.exe"

fileSuffix="hardQCD"

inputFile="./out/events/qcd/pythiaGenerateAndWrite_"$fileSuffix".root"

tagList=(
"parton"
"quark"
"gluon"
"parton"
"quark"
"gluon"
);

tagStatusList=(
"0"
"0"
"0"
"1"
"1"
"1"
);

probeStatusList=(
"0"
"0"
"0"
"0"
"0"
"0"
);

arrayIndices=${!tagList[*]}
for i1 in $arrayIndices
do
    tag=${tagList[i1]}
    tagStatus=${tagStatusList[i1]}
    probeStatus=${probeStatusList[i1]}

    outputFileTmp="./out/analysis/qcd/hardScatteringAna_"$fileSuffix"_XTag_tagYY_probeZZ.root"
    outputFile="${outputFileTmp/_X/_${tag}}"

    tagStatusStr=""
    if [[ $tagStatus = 0 ]]; then
      tagStatusStr="Hard"
    elif [[ $tagStatus = 1 ]]; then
      tagStatusStr="Out"
    fi

    probeStatusStr=""
    if [[ $probeStatus = 0 ]]; then
      probeStatusStr="Hard"
    elif [[ $probeStatus = 1 ]]; then
      probeStatusStr="Out"
    fi

    outputFile="${outputFile/_tagYY/_tag${tagStatusStr}}"
    outputFile="${outputFile/_probeZZ/_probe${probeStatusStr}}"

    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $inputFile $outputFile $tag $tagStatus $probeStatus &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile $tag $tagStatus $probeStatus &> $outputFileLOG &"
    wait
done


