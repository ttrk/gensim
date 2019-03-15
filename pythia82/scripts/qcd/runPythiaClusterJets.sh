#!/bin/bash

fileSuffix="hardQCD"
inputFile="./out/events/qcd/pythiaGenerateAndWrite_"$fileSuffix".root"
outputFile="./out/jets/qcd/pythiaClusterJets_"$fileSuffix".root"

./scripts/runPythiaClusterJets.sh $inputFile $outputFile

