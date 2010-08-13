#!/bin/bash
# Bash script to link while renaming the different totouples (UserCode/IpnTreeProducer/test/partI/partI__run_133483/MinimumBias_Commissioning10-SD_Mu-Jun14thSkim_v1_RECO_IpnTree_3_1_dac.root into Zmumugamma/RecoSamples/partI/partI__run_133483_IpnTree_3_1_dac.root)
# Written by Olivier Bondu (July 2010)
# This script is independent of the CMSSW release

syntax="Syntax ${0} {partX}"

if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi

partX=${1}
if [[ ! -e ${partX} ]]
then
  mkdir ${partX}
fi


for sample in `'ls' ../../UserCode/IpnTreeProducer/test/${partX} | grep ${partX}__`
do
	echo ${sample}
	for file in `'ls' ../../UserCode/IpnTreeProducer/test/${partX}/${sample} | grep root`
	do
		endname=`echo ${file} | rev | cut -d _ -f -4 | rev`
		newfilename=`echo ${sample}_${endname}`
#		echo ${newfilename}
		ln -s ../../../UserCode/IpnTreeProducer/test/${partX}/${sample}/${file} ./${partX}/${newfilename}
	done
done





exit 0
