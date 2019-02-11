#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

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
## smeared jets
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
## smeared jets
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
## smeared jets
"3"
"4"
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
## smeared jets
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
## smeared jets
"0"
"0"
);

noSmearJetpt="0,0,0"
jetptCSNs=(
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
## smeared jets
"0.06,0.95,0"
"0.06,0.95,0"
);

noSmearJetphi="0,0,0"
jetphiCSNs=(
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
## smeared jets
"0.000000772,0.1222,0.5818"
"0.000000772,0.1222,0.5818"
);

arrayIndices=${!outputFiles[*]}
for i1 in $arrayIndices
do
    inputFile=${inputFiles[i1]}
    outputFile=${outputFiles[i1]}
    jetRadius=${jetRadii[i1]}
    minJetPt=${minJetPts[i1]}
    constituentType=${constituentTypes[i1]}

    jetptCSN=""
    if [[ ! ${jetptCSNs[i1]} = ${noSmearJetpt} ]]; then
      jetptCSN=${jetptCSNs[i1]}
    fi
    jetphiCSN=""
    if [[ ! ${jetphiCSNs[i1]} = ${noSmearJetphi} ]]; then
      jetphiCSN=${jetphiCSNs[i1]}
    fi

    outputFileLOG="${outputFile/.root/_R${jetRadius}_minPt${minJetPt}_constituentType${constituentType}.log}"
    if [ ! -z ${jetptCSN} ]; then
      strCSN="${jetptCSN//,/_}"  ## 0.2,0.187 --> 0.2_0.187
      strCSN="${strCSN//./p}"    ## 0.2 --> 0p2
      outputFileLOG="${outputFileLOG/.log/_smearJetPt_CSN_${strCSN}.log}"
    fi
    if [ ! -z ${jetphiCSN} ]; then
      strCSN="${jetphiCSN//,/_}"
      strCSN="${strCSN//./p}"
      outputFileLOG="${outputFileLOG/.log/_smearJetPhi_CSN_${strCSN}.log}"
    fi

    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir
    $runCmd $progPath $inputFile $outputFile $jetRadius $minJetPt $constituentType $jetptCSN $jetphiCSN &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile $jetRadius $minJetPt $constituentType $jetptCSN $jetphiCSN &> $outputFileLOG &"
    wait
done


