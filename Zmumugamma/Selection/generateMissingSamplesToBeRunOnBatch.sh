#!/bin/bash
# Small script to generate the file which will run the selection on all the samples that have not been run yet
# Written by Olivier Bondu (March 2010)

CMSSW_release="CMSSW_3_9_7_v2"

sampleDirectory=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/RecoSamples

for sample in `'ls' -l ${sampleDirectory} | grep drw | awk '{print $9}' | grep -v CVS`
do
	for selection in `echo "hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2"`
#	for selection in `echo "hadEt-noDeltaRmin-relaxedMuEta hadEt-noDeltaRmin-relaxedMuEta-relaxedGammaPt hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2"`
	do
		if [[ `cat runAllSplittedOnBatch.sh | grep ${sample} | grep -w ${selection}` ]]
		then
			continue
		fi
		echo "./runThisSplittedOnBatch.sh ${sample} ${selection}"
	done
done


exit 0


