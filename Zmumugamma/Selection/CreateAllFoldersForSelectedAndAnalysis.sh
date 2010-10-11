#!/bin/bash
# Small script to run CreateFoldersForSelectedAndAnalysis.sh for all selections in one shot
# Written by Olivier Bondu (March 2010)

#for selection in `echo "hadEt noMuIso-hadEt sumPt noMuIso-sumPt noMuIso-hadEt-noDeltaRmin hadEt-noDeltaRmin hadEt-noDeltaRmin-relaxedpT hadEt-lowDeltaRmin hadEt-noDeltaRmin-tightedPtMu hadEt-noDeltaRmin-relaxedMuEta"`
#for selection in `echo "hadEt-noDeltaRmin-relaxedpT-looseWindow"`
EScaleList=""
for scale in `seq -w 0.95 0.005 1.05`
do
	EScaleList=`echo "${EScaleList}hadEt-noDeltaRmin-singleTightedPtMu-${scale}EScale "`
done
for selection in `echo "${EScaleList} hadEt-noDeltaRmin-singleTightedPtMu"`
do
	./CreateFoldersForSelectedAndAnalysis.sh ${selection}
done

exit 0
