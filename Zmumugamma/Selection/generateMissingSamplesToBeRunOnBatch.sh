#!/bin/bash
# Small script to generate the file which will run the selection on all the samples that have not been run yet
# Written by Olivier Bondu (March 2010)

CMSSW_release="CMSSW_3_6_1_patch4"

sampleDirectory=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/RecoSamples

for sample in `'ls' -l ${sampleDirectory} | grep drw | awk '{print $9}' | grep -v CVS`
do
	if [[ `cat runAllSplittedOnBatch.sh | grep ${sample}` ]]
	then
		continue
	fi
	for selection in `echo "hadEt noMuIso-hadEt"`
	do
		echo "./runThisSplittedOnBatch.sh ${sample} ${selection}"
	done
	echo ""
done


exit 0

#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-hadEt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-hadEt01
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-sumPt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma CUT5-sumPt01
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma NORMAL-hadEt
#./runThisSplittedOnBatch.sh 7TeV_Zmumugamma NORMAL-sumPt

