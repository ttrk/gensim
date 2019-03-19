#!/bin/bash

if [ $# -lt 3 ]; then
  echo "Usage: ./scripts/runParticleTreeClusterJets.sh [input file] [output file] [treePath]"
  echo "Example: ./scripts/runParticleTreeClusterJets.sh ../toy/sampleToyEvents.root ../toy/particleTreeClusterJets.root evtHydjet"
  exit 1
fi

inputFile=${1}
outputFile=${2}
treePath=${3}

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./particleTreeClusterJets.exe"

jetRadii=(
"3"
"3"
"3"
"4"
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
);

jetTypes=(
"0"
"1"
"2"
"0"
"1"
"2"
);

noSmearJetpt="0,0,0"
jetptCSNs=(
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
$noSmearJetpt
#"0.06,0.95,0"
);

noSmearJetphi="0,0,0"
jetphiCSNs=(
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
$noSmearJetphi
#"0.000000772,0.1222,0.5818"
);

arrayIndices=${!jetRadii[*]}
for i1 in $arrayIndices
do
    jetRadius=${jetRadii[i1]}
    minJetPt=${minJetPts[i1]}
    jetType=${jetTypes[i1]}

    jetptCSN=""
    if [[ ! ${jetptCSNs[i1]} = ${noSmearJetpt} ]]; then
      jetptCSN=${jetptCSNs[i1]}
    fi
    jetphiCSN=""
    if [[ ! ${jetphiCSNs[i1]} = ${noSmearJetphi} ]]; then
      jetphiCSN=${jetphiCSNs[i1]}
    fi

    outputFileLOG="${outputFile/.root/_R${jetRadius}_minPt${minJetPt}_jetType${jetType}.log}"
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
    $runCmd $progPath $inputFile $outputFile $treePath $jetRadius $minJetPt $jetType $jetptCSN $jetphiCSN &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile $treePath $jetRadius $minJetPt $jetType $jetptCSN $jetphiCSN &> $outputFileLOG &"
    wait
done


