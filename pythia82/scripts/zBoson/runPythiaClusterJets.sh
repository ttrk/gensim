#!/bin/bash

fileSuffix="ZmmJet"
inputFile="./out/events/zBoson/pythiaGenerateAndWrite_"$fileSuffix".root"
outputFile="./out/jets/zBoson/pythiaClusterJets_"$fileSuffix".root"

./scripts/runPythiaClusterJets.sh $inputFile $outputFile

