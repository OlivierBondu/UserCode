#!/bin/bash
# Small script to run CreateFoldersForSelectedAndAnalysis.sh for all selections in one shot
# Written by Olivier Bondu (March 2010)

EScaleList=""
for scale in `seq -w 0.950 0.001 1.05`
do
  EScaleList=`echo "${EScaleList}hadEt-noDeltaRmin-relaxedMuEta_EScale-${scale} "`
done
#for selection in `echo "${EScaleList}"`
for selection in `echo "hadEt-noDeltaRmin-relaxedMuEta"`
do
	./CreateFoldersForSelectedAndAnalysis.sh ${selection}
done

exit 0
