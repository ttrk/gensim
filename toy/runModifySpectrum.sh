#!/bin/bash

runCmd=$MYRUN

progPath="./modifySpectrum.exe"

## Function 1
# pt spectrum
specFormula="[0]*TMath::Power(60/x,[1])"
xMin1="30"
xMax1="130"
parValues1="0.0593128;4.51425"
spec=$specFormula";"$xMin1";"$xMax1";"$parValues1

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

outputFile="./out_modifySpectrum.root"

mode=0
outputFileLOG="${outputFile/.root/.log}"
outDir=$(dirname "${outputFile}")
mkdir -p $outDir
$runCmd $progPath $mode $spec $modifier $outputFile &> $outputFileLOG &
echo "$runCmd $progPath $mode $spec $modifier $outputFile &> $outputFileLOG &"

