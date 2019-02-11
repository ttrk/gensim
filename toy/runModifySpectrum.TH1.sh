#!/bin/bash

runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./modifySpectrum.exe"

## Function 1
# pt spectrum
PT0=30
specFile="input/spectra_jtpt_refpt.root"
specPath="h_1_normInt"
xMin1="30"
xMax1="200"
spec=$specFile";"$specPath";"$xMin1";"$xMax1

## Function 2
# Gaussian smearing of energy measurement
# [Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma]))
sigmaCSN="TMath::Sqrt([0]*[0]+[1]*[1]/([3])+[2]*[2]/([3]*[3]))"
modifierFormula="exp(-0.5*((x-1)/"$sigmaCSN")*((x-1)/"$sigmaCSN"))"
xMin2="0"
xMax2="2"
parValues2="0.06;0.95;0"  # CSN PP = {0.06, 0.95, 0};
#parValues2="0.06;1.241;6.827"  # CSN HI cent0030 = {0.06, 1.241, 6.827};
#parValues2="0.06;1.241;8.421"  # CSN HI cent0010 = {0.06, 1.241, 8.421};
modifier=$modifierFormula";"$xMin2";"$xMax2";"$parValues2

outputFile="./out_modifySpectrum_TH1.root"

mode=1
outputFileLOG="${outputFile/.root/.log}"
outDir=$(dirname "${outputFile}")
mkdir -p $outDir
$runCmd $progPath $mode $spec $modifier $outputFile &> $outputFileLOG &
echo "$runCmd $progPath $mode $spec $modifier $outputFile &> $outputFileLOG &"

