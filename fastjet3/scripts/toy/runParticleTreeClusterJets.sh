#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

fileSuffix="sampleToyEvents_cent010_N5000"
inputFile="../toy/"$fileSuffix".root"
outputFile="../toy/particleTreeClusterJets_"$fileSuffix".root"
treePath="evtToyHydjet"
./scripts/runParticleTreeClusterJets.sh $inputFile $outputFile $treePath

