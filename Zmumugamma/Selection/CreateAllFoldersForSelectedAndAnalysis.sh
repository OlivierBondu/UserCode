#!/bin/bash
# Small script to run CreateFoldersForSelectedAndAnalysis.sh for all selections in one shot
# Written by Olivier Bondu (March 2010)

#for selection in `echo "hadEt noMuIso-hadEt sumPt noMuIso-sumPt noMuIso-hadEt-noDeltaRmin hadEt-noDeltaRmin hadEt-noDeltaRmin-relaxedpT hadEt-lowDeltaRmin hadEt-noDeltaRmin-tightedPtMu hadEt-noDeltaRmin-relaxedMuEta"`
for selection in `echo "hadEt-noDeltaRmin-relaxedpT-looseWindow"`
do
	./CreateFoldersForSelectedAndAnalysis.sh ${selection}
done

exit 0
