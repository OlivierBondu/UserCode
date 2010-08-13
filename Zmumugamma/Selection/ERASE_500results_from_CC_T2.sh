#!/bin/bash
# Bash script to empty the directories where the crab results staged out are on the CC IN2P3 Tier2 
# Written by Olivier Bondu (February 2010)
# This script is independent of the CMSSW release


syntax="Syntax ${0} {sampleName}"
if [[ -z ${1} ]]
then
  echo ${syntax}
	exit 1
fi

sampleName=${1}
workingDir=`pwd`

T2machine="srm://ccsrmt2.in2p3.fr:8443"
T2manager="/srm/managerv2?SFN="
T2filepath="/pnfs/in2p3.fr/data/cms/t2data/store/user/obondu/"

srmls -count=500 ${T2machine}${T2manager}${T2filepath} | grep ${sampleName} &> /dev/null
if [[ $? == 1 ]]
then
	echo "WARNING: this sample is not on T2"
	exit 2
fi

totalNBofFilesToBeErased=`srmls -count=500 ${T2machine}${T2manager}${T2filepath}${sampleName} | grep -v " 0 " | awk --field-separator "${sampleName}/" '{print $2}' | wc -l`
totalNBofFilesToBeErased=$[${totalNBofFilesToBeErased}-3]
counter=0
for file in `srmls -count=500 ${T2machine}${T2manager}${T2filepath}${sampleName} | grep -v " 0 " | awk --field-separator "${sampleName}/" '{print $2}'`
do
#	srmmv ${T2machine}${T2filepath}${sampleName}/${file} file:///${sampleName}/.
#	srmcp ${T2machine}${T2filepath}${sampleName}/${file} file:///${sampleName}/.
	srmrm ${T2machine}${T2filepath}${sampleName}/${file}
	counter=$[${counter}+1]
	echo "(${counter} / ${totalNBofFilesToBeErased}) ${file} ERASED"
done
srmrmdir ${T2machine}${T2filepath}${sampleName}
echo -e "\t Directory ${T2machine}${T2filepath}${sampleName} ERASED"

exit 0


