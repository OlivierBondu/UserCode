#!/bin/bash
# Bash script to get the crab results staged out on the CC IN2P3 Tier2 
# Written by Olivier Bondu (January 2010)
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

srmls ${T2machine}${T2manager}${T2filepath} | grep ${sampleName} &> /dev/null
if [[ $? == 1 ]]
then
	echo "WARNING: this sample is not on T2"
	exit 2
fi

totalNBofFilesToBeMigrated=`srmls ${T2machine}${T2manager}${T2filepath}${sampleName}/${sampleName} | grep -v " 0 " | awk --field-separator "${sampleName}/" '{print $3}' | grep root | wc -l`
#totalNBofFilesToBeMigrated=$[${totalNBofFilesToBeMigrated}-1]
#echo "totalNBofFilesToBeMigrated= ${totalNBofFilesToBeMigrated}"

counter=0
for file in `srmls ${T2machine}${T2manager}${T2filepath}${sampleName}/${sampleName} | grep -v " 0 " | awk --field-separator "${sampleName}/" '{print $3}' | grep root`
do
#	echo ${file}
#	srmmv ${T2machine}${T2filepath}${sampleName}/${file} file:///${sampleName}/.
	srmcp ${T2machine}${T2filepath}${sampleName}/${sampleName}/${file} file:///${sampleName}/.
	counter=$[${counter}+1]
	echo "(${counter} / ${totalNBofFilesToBeMigrated}) ${file} treated"
done

exit 0


