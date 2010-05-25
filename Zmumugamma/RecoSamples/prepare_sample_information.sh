#!/bin/bash
# Bash script to prepare the information about the sample used
# Written by Olivier Bondu (April 2010)
# This script is independent of the CMSSW release
# Needs as input: the twiki page where all the info is available in a formatted way, and the sample_list.txt file containing the different datasets

for dataset in `cat sample_list.txt`
do
	sampleName=`echo "${dataset}" | cut -d / -f -2 | rev  | cut -d / -f -1 | rev`
	processID=`cat ProductionReProcessingSpring10.htm | grep -B 3 "/${sampleName}/" | grep twikiTableCol0 | cut -d \> -f 2- | cut -d \< -f -1 | awk '{print $1}' | head -1`
	iCrossSectionColumn=9
	echo ${sampleName} | grep alpgen &> /dev/null
	isAlpgen=$?
	echo ${sampleName} | grep mcatnlo &> /dev/null
  isMCatnlo=$?
  echo ${sampleName} | grep madgraph &> /dev/null
  isMadgraph=$?
	if [[ ${isAlpgen} == 0 ]]
	then iCrossSectionColumn=10
	fi
	if [[ ${isMCatnlo} == 0 ]]
  then iCrossSectionColumn=10
	fi
	if [[ ${isMadgraph} == 0 ]]
  then iCrossSectionColumn=10
	fi

	crossSection=`cat ProductionReProcessingSpring10.htm | grep -A 12 "/${sampleName}/" | grep twikiTableCol${iCrossSectionColumn} | cut -d \> -f 2- | cut -d \< -f -1 | awk '{print $1}' | head -1`
	echo -e "${processID} ${sampleName}\t ${crossSection}"
done






exit 0
for cat ProductionReProcessingSpring10.htm | grep -B 3 PhotonJet_Pt0to15 | grep twikiTableCol0 | awk '{print $6}'


echo "Preparing information on samples"
if [[ -z ${1} ]]
then
	echo "Syntax ${0} {sampleName} {dbsPath} {crossSection} {signalGenerator}"
	exit 1
else
	if [[ -z ${2} ]]
	then
		echo "Syntax ${0} {sampleName} {dbsPath} {crossSection} {signalGenerator}"
  	exit 1
	else
		if [[ -z ${3} ]]
		then
			echo "Syntax ${0} {sampleName} {dbsPath} {crossSection} {signalGenerator}"
			exit 1
		else
			if [[ -z ${4} ]]
			then
				echo "Syntax ${0} {sampleName} {dbsPath} {crossSection} {signalGenerator}"
				exit 1
			fi
		fi
	fi
fi

sampleName=${1}
dbsPath=${2}
crossSection=${3}
signalGenerator=${4}
workingDir=`pwd`
currentDate=`date`

# First look if this sample have already been treated
#if [ -d ${sampleName} ]
#then
#	rm -r ${sampleName}
#else
#	mkdir ${sampleName}
#	echo "Directory ${sampleName} CREATED"
#fi

# Second : create the appropriate python config file from template
cp toto_RECO_template.py toto_RECO_${sampleName}.py
sed -i -e s,COMMENTS,"This file has been created with\n\# ${0} ${1} ${2} ${3} ${4}\n\# ${currentDate}",g toto_RECO_${sampleName}.py
sed -i -e s,OUTPUTFILE,Toto_${sampleName}.root,g toto_RECO_${sampleName}.py
sed -i -e s,XSECTION,${crossSection},g toto_RECO_${sampleName}.py
sed -i -e s,DESCRIPTION,${dbsPath},g toto_RECO_${sampleName}.py
sed -i -e s,SIGNALGENERATOR,${signalGenerator},g toto_RECO_${sampleName}.py
echo "CMSSW config file toto_RECO_${sampleName}.py CREATED"

# Third : create the appropriate crab config file from template
cp crab_template.cfg crab_${sampleName}.cfg
sed -i -e s,PYTHONFILE,toto_RECO_${sampleName}.py,g crab_${sampleName}.cfg
sed -i -e s,DATAPATH,${dbsPath},g crab_${sampleName}.cfg
sed -i -e s,OUTPUTFILE,Toto_${sampleName}.root,g crab_${sampleName}.cfg
sed -i -e s,SAMPLENAME,${sampleName},g crab_${sampleName}.cfg
echo "CRAB config file crab_${sampleName}.cfg CREATED"

# Fourth : display information about sage of the newly created files
echo "*** To submit the jobs do :"
echo "crab -create -cfg crab_${sampleName}.cfg; crab -submit -c ${sampleName}"

exit 0
