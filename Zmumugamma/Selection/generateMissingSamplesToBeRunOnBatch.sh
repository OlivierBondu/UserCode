#!/bin/bash
# Small script to generate the file which will run the selection on all the samples that have not been run yet
# Written by Olivier Bondu (March 2010)

CMSSW_release="CMSSW_3_6_1_patch4"

sampleDirectory=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/RecoSamples

for sample in `'ls' -l ${sampleDirectory} | grep drw | awk '{print $9}' | grep -v CVS`
do
	EScaleList=""
	for scale in `seq -w 0.95 0.005 1.05`
	do
	  EScaleList=`echo "${EScaleList}hadEt-noDeltaRmin-singleTightedPtMu-${scale}Escale "`
	done
	for selection in `echo "${EScaleList} hadEt-noDeltaRmin-singleTightedPtMu"`
#	for selection in `echo "hadEt noMuIso-hadEt sumPt noMuIso-sumPt noMuIso-hadEt-noDeltaRmin hadEt-noDeltaRmin hadEt-noDeltaRmin-relaxedpT hadEt-lowDeltaRmin hadEt-noDeltaRmin-tightedPtMu hadEt-noDeltaRmin-relaxedMuEta hadEt-noDeltaRmin-relaxedpT-looseWindow"`
	do
		if [[ `cat runAllSplittedOnBatch.sh | grep ${sample} | grep -w ${selection}` ]]
		then
			continue
		fi
		echo "./runThisSplittedOnBatch.sh ${sample} ${selection}"
	done
done


exit 0

#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-hadEt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-hadEt01
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-sumPt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-sumPt01
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma NORMAL-hadEt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma NORMAL-sumPt

