#!/bin/bash

runCmd=$MYRUN

progPath="./modifySpectrum.exe"

## Function 1
# pt spectrum
fnc1Formula="[0]*TMath::Power(60/x,[1])"
xMin1="30"
xMax1="130"
parValues1="0.0593128;4.51425"
fnc1=$fnc1Formula";"$xMin1";"$xMax1";"$parValues1

## Function 2
# Gaussian smearing of energy measurement
# [Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma]))
sigmaCSN="TMath::Sqrt([0]*[0]+[1]*[1]/([3])+[2]*[2]/([3]*[3]))"
fnc2Formula="exp(-0.5*((x-1)/"$sigmaCSN")*((x-1)/"$sigmaCSN"))"
xMin2="0"
xMax2="2"
parValues2="0.06;0.95;0"  # CSN PP = {0.06, 0.95, 0};
#parValues2="0.06;1.241;6.827"  # CSN HI cent0030 = {0.06, 1.241, 6.827};
#parValues2="0.06;1.241;8.421"  # CSN HI cent0010 = {0.06, 1.241, 8.421};
fnc2=$fnc2Formula";"$xMin2";"$xMax2";"$parValues2

outputFile="./out_modifySpectrum.root"

outputFileLOG="${outputFile/.root/.log}"
outDir=$(dirname "${outputFile}")
mkdir -p $outDir
$runCmd $progPath $fnc1 $fnc2 $outputFile &> $outputFileLOG &
echo "$runCmd $progPath $fnc1 $fnc2 $outputFile &> $outputFileLOG &"

