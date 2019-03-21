#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./analysis/eventInfoAna.exe"

#fileSuffix="promptPhoton"
fileSuffix="promptPhoton_off_MPI_ISR_FSR_BR"

inputFile="./out/events/photon/pythiaGenerateAndWrite_"${fileSuffix}".root"

processCodes=("-1"       "201"            "202,203")
processCodesSuffixes=("" "_proc_x2qgamma" "_proc_x2ggamma")

qMins=(0  60  100)
qMaxs=(-1 100 -1)
qSuffixes=("" "_q60100" "_q100")

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

    outputFileTmp="./out/analysis/photon/eventInfoAna_"${fileSuffix}".root"
    outputFile="${outputFileTmp/.root/${processCodeSuffix}${qSuffix}.root}"
    outputFileLOG="${outputFile/.root/.log}"
    outDir=$(dirname "${outputFile}")
    mkdir -p $outDir

    $runCmd $progPath $inputFile $outputFile --processList=${processCode} --qMin=${qMin} --qMax=${qMax} &> $outputFileLOG &
    echo "$runCmd $progPath $inputFile $outputFile --processList=${processCode} --qMin=${qMin} --qMax=${qMax} &> $outputFileLOG &"
  done
done


