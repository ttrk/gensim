#!/bin/bash

export PYTHIA8DATA=$PYTHIA82/share/Pythia8/xmldoc/
runCmd=""
if [ ! -z ${MYRUN} ]; then
  runCmd=${MYRUN}
fi

progPath="./eventInfoAna.exe"

inputFiles=(
"./out/events/photon/pythiaGenerateAndWrite_promptPhoton.root"
);

outputFiles=(
"./out/analysis/photon/eventInfoAna_promptPhoton.root"
);

processCodes=("-1" "201" "202,203")
processCodesSuffixes=("" "_proc201" "_proc202203")

qMins=(0  60  100)
qMaxs=(-1 100 -1)
qSuffixes=("" "_scale60100" "_scale100")

arrayIndices=${!outputFiles[*]}
indicesProcessCodes=${!processCodes[*]}
indicesqMins=${!qMins[*]}
for i1 in $arrayIndices
do
  for i2 in $indicesProcessCodes
  do
    for i3 in $indicesqMins
    do
      inputFile=${inputFiles[i1]}

      processCode=${processCodes[i2]}
      processCodeSuffix=${processCodesSuffixes[i2]}

      qMin=${qMins[i3]}
      qMax=${qMaxs[i3]}
      qSuffix=${qSuffixes[i3]}

      outputFileTmp=${outputFiles[i1]}
      outputFile="${outputFileTmp/.root/${processCodeSuffix}${qSuffix}.root}"
      outputFileLOG="${outputFile/.root/.log}"
      outDir=$(dirname "${outputFile}")
      mkdir -p $outDir
      $runCmd $progPath $inputFile $outputFile $processCode $qMin $qMax &> $outputFileLOG &
      echo "$runCmd $progPath $inputFile $outputFile $processCode $qMin $qMax &> $outputFileLOG &"
    done
  done
done


