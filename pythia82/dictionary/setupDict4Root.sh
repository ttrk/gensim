#!/bin/bash
# set up Pythia dictionary for ROOT.

if [ $# -lt 1 ]; then
  echo "Usage: ./setupDict4Root.sh <pythiaExamplesDir>"
  echo "<pythiaExamplesDir> = directory for pythia examples which contains main92 files, the ROOT dictionary files for Pythia"
  echo "Example : ./setupDict4Root.sh ../../../pythia8223/examples"
  exit 1
fi

# path to Pythia examples directory which contains main92 files
# Pythia example main92 contains the ROOT dictionary files for Pythia
pythiaExamplesDir=$1
pathDict4RootH=$pythiaExamplesDir"/main92.h"
pathDict4RootCC=$pythiaExamplesDir"/main92Dct.cc"
pathDict4RootPCM=$pythiaExamplesDir"/main92Dct_rdict.pcm"
pathDict4RootLinkDef=$pythiaExamplesDir"/main92LinkDef.h"

set -x
cp $pathDict4RootH dict4Root.h
cp $pathDict4RootCC dict4RootDct.cc
cp $pathDict4RootPCM dict4RootDct_rdict.pcm
cp $pathDict4RootLinkDef dict4RootLinkDef.h
set +x

# replacements for dict4Root.h
tmpFile="dict4Root.h"

lineToReplace="main92.h"
newLine="dict4Root.h"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="using namespace Pythia8;"
newLine="\/\/using namespace Pythia8;      \/\/ do not \"use namespace\" to avoid the following error \"reference to ‘ROOT’ is ambiguous\""
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

# replacements for dict4RootLinkDef.h
tmpFile="dict4RootLinkDef.h"

lineToReplace="main92LinkDef.h"
newLine="dict4RootLinkDef.h"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

# replacements for dict4Root.h and dict4RootLinkDef.h
lineToReplace="\/\/ Please respect the MCnet Guidelines, see GUIDELINES for details."
newLine=$lineToReplace"\n\/\/ derived from main92.cc example of PYTHIA 8.2."
sed -i "s/$lineToReplace/$newLine/g" dict4Root.h
sed -i "s/$lineToReplace/$newLine/g" dict4RootLinkDef.h

# replacements for dict4RootDct.cc
tmpFile="dict4RootDct.cc"

lineToReplace="\/\/ Do NOT change. Changes will be lost next time file is generated"
newLine=$lineToReplace"\n\/\/ derived from main92.cc example of PYTHIA 8.2."
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="R__DICTIONARY_FILENAME main92Dct"
newLine="R__DICTIONARY_FILENAME dict4RootDct"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="#include \"main92.h\""
newLine="#include \"dict4Root.h\""
sed -i "0,/$lineToReplace/s/$lineToReplace/$newLine/" $tmpFile  # replace only the first instance

lineToReplace="_main92Dct"
newLine="_dict4RootDct"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="\"main92.h\""
newLine="\"dictionary\/dict4Root.h\""
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="\"..\/include\""
newLine="Form\(\"%s\/include\", std::getenv\(\"PYTHIA82\"\)\)"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

sed -i '/examples/d' $tmpFile  # remove the line with reference to "examples" directory

lineToReplace="main92Dct dictionary"
newLine="dict4RootDct dictionary"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="\$main92.h"
newLine="\$dictionary\/dict4Root.h"
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

lineToReplace="\"main92Dct\""
newLine="\"dictionary\/dict4RootDct\""
sed -i "s/$lineToReplace/$newLine/g" $tmpFile

