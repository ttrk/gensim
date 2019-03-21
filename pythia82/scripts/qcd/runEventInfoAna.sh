#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./eventInfoAna.exe"

#fileSuffix="hardQCD"
fileSuffix="hardQCD_off_MPI_ISR_FSR_BR"

inputFile="./out/events/qcd/pythiaGenerateAndWrite_"${fileSuffix}".root"

processCodes=("-1"       "113"        "111,115"    "112,114,116,121,122,123,124")
processCodesSuffixes=("" "_proc_x2qg" "_proc_x2gg" "_proc_x2qqbar")

qMins=(0  80  220)
qMaxs=(-1 220 -1)
qSuffixes=("" "_q80220" "_q220")

indicesProcessCodes=${!processCodes[*]}
indicesqMins=${!qMins[*]}
for i2 in $indicesProcessCodes
do
  for i3 in $indicesqMins
  do
    processCode=${processCodes[i2]}
    processCodeSuffix=${processCodesSuffixes[i2]}

    qMin=${qMins[i3]}
    qMax=${qMaxs[i3]}
    qSuffix=${qSuffixes[i3]}

    outputFileTmp="./out/analysis/qcd/eventInfoAna_"${fileSuffix}".root"
    outputFile="${outputFileTmp/.root/${processCodeSuffix}${qSuffix}.root}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $inputFile $outputFile --processList=${processCode} --qMin=${qMin} --qMax=${qMax} &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile --processList=${processCode} --qMin=${qMin} --qMax=${qMax} &> $outputFileLOG &"
  done
done

