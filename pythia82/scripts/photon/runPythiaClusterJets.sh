#!/bin/bash

## prompt photon
fileSuffix="promptPhoton"
inputFile="./out/events/photon/pythiaGenerateAndWrite_"$fileSuffix".root"
outputFile="./out/jets/photon/pythiaClusterJets_"$fileSuffix".root"

./scripts/runPythiaClusterJets.sh $inputFile $outputFile

