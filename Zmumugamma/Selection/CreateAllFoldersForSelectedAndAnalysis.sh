#!/bin/bash
# Small script to run CreateFoldersForSelectedAndAnalysis.sh for all selections in one shot
# Written by Olivier Bondu (March 2010)

for selection in `echo "hadEt noMuIso-hadEt sumPt noMuIso-sumPt noMuIso-hadEt-noDeltaRmin"`
do
	./CreateFoldersForSelectedAndAnalysis.sh ${selection}
done

exit 0
