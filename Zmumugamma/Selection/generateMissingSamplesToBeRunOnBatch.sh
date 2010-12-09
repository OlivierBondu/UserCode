#!/bin/bash
# Small script to generate the file which will run the selection on all the samples that have not been run yet
# Written by Olivier Bondu (March 2010)

CMSSW_release="CMSSW_3_8_6_v6"

sampleDirectory=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/RecoSamples

for sample in `'ls' -l ${sampleDirectory} | grep drw | awk '{print $9}' | grep -v CVS`
do
	for selection in `echo "hadEt-noDeltaRmin-relaxedMuEta"`
	do
		if [[ `cat runAllSplittedOnBatch.sh | grep ${sample} | grep -w ${selection}` ]]
		then
			continue
		fi
		echo "./runThisSplittedOnBatch.sh ${sample} ${selection}"
	done
done


exit 0


