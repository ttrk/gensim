#!/bin/bash

if [ $# -lt 2 ]; then
  echo "Usage: ./scripts/runPythiaClusterJets.sh [input file] [output file]"
  echo "Example: ./scripts/runPythiaClusterJets.sh ./out/events/pythiaGenerateAndWrite.root ./out/jets/photon/pythiaClusterJets.root"
  exit 1
fi

inputFile=${1}
outputFile=${2}

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./pythiaClusterJets.exe"

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
"6"
"7"
"8"
"8"
"8"
## smeared jets
"3"
"4"
## WTA
"3"
"3"
"4"
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
"5"
## smeared jets
"5"
"5"
## WTA
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
"0"
"2"
"3"
## smeared jets
"0"
"0"
## WTA
"6"
"6"
"6"
"6"
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
$noSmearJetpt
## smeared jets
"0.06,0.95,0"
"0.06,0.95,0"
## WTA
$noSmearJetpt
"0.06,0.95,0"
$noSmearJetpt
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
$noSmearJetphi
## smeared jets
"0.000000772,0.1222,0.5818"
"0.000000772,0.1222,0.5818"
## WTA
$noSmearJetphi
"0.000000772,0.1222,0.5818"
$noSmearJetphi
"0.000000772,0.1222,0.5818"
);

arrayIndices=${!jetRadii[*]}
for i1 in $arrayIndices
do
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


