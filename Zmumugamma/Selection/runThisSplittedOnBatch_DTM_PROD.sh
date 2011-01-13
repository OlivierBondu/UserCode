#!/usr/local/bin/bash
# Small script to run the selection code on the anastasie CC IN2P3 batch cluster
# Written by Olivier Bondu (January 2010) for CMSSW 3_1_4
CMSSWversion=CMSSW_3_8_6_v6

HOME=/afs/in2p3.fr/home/o/obondu
WORKINGDIR=/sps/cms/obondu/${CMSSWversion}/src/Zmumugamma/Selection
RECODIR=/sps/cms/obondu/${CMSSWversion}/src/Zmumugamma/RecoSamples

syntax="Syntax: ${0} {SampleName} {cutVersion}"
if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
else
  SampleName=${1}
  if [[ -z ${2} ]]
  then
    echo ${syntax}
    exit 1
  else
    cutVersion=${2}
    version="_${cutVersion}"
    versionpath="SVG/"
    fi
fi


NumberOfFiles=`ls ${RECODIR}/${SampleName}/${SampleName}_*.root | wc -l`
'ls' ${RECODIR}/${SampleName}/${SampleName}_*.root > TEMP_FileList_${SampleName}
RawSampleName=`echo ${SampleName}`


	echo "*********************************************"
	echo "*********************************************"
	echo "*** Sample ${SampleName} version ${cutVersion}"
	echo "*********************************************"
	echo "*********************************************"

# STOP RIGHT NOW IF THERE IS NO INPUT FILE
echo "Number of input files : $NumberOfFiles"
if [ "${NumberOfFiles}" = "0" ]
    then echo "ERROR : No input file"
    exit 2
fi


# GENERIC REQUIREMENTS (OVERWRITTEN LATER BY SPECIFIC ONES)
NumberOfIpnTreeFilesToRunInOneJob=200
time=680000
memory="1024MB"
stew="false"
zjetveto="false"
powheg="false"
signal="true" # all samples are passed with tight mumugamma mass window
verbosity="off"
minPtHat="-100"
maxPtHat="1000000"
prodName="${SampleName}"

# SPECIFIC REQUIREMENTS (TODO: add other samples)
if [ "${SampleName}" = "TTbarJets_Tauola-madgraph" ]
then
  NumberOfIpnTreeFilesToRunInOneJob=500
#  time=570000
	time=285000
#elif [ "${SampleName}" = "" ]
#then
#  minPtHat="-100"
#  maxPtHat="1000000"
# time=
fi

echo "${SampleName}" | grep part > /dev/null
if [ "$?" = "0" ]
then
  verbosity="on"
else
  verbosity="off"
fi

if [ "${SampleName}" = "DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia" ]
then
  NumberOfIpnTreeFilesToRunInOneJob=50
  zjetveto="true"
  powheg="true"
	prodName="DYToMuMu-powheg"
#	time=18000
fi




# IF SAMPLE IS DATA, SWITCH VERBOSITY ON
echo "${SampleName}" | grep part > /dev/null
if [ "$?" = "0" ]
then
  verbosity="on"
fi

#FIXME rm -f ${SampleName}${version}*
begin=1
let "NumberOfJobs=NumberOfFiles/NumberOfIpnTreeFilesToRunInOneJob"
let "NumberOfJobsMinus1=NumberOfJobs-1"
let "rest=NumberOfFiles-NumberOfIpnTreeFilesToRunInOneJob*NumberOfJobs"

# PREPARING PRE-MACRO FILE
echo "Preparing pre-macro file..."
sed -e "s/signal = false/signal = ${signal}/1" ${versionpath}Selection_miniTree${version}.C > Selection_miniTree_${SampleName}.C
sed -i -e "s/stew = false/stew = ${stew}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/zjet_veto = false/zjet_veto = ${zjetveto}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/bool doSignalMuMuGamma        = false/bool doSignalMuMuGamma        = ${zjetveto}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/powheg = false/powheg = ${powheg}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/minPtHat = -100;/minPtHat = ${minPtHat};/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/maxPtHat = 1000000;/maxPtHat = ${maxPtHat};/1" Selection_miniTree_${SampleName}.C
if [ "${verbosity}" = "on" ]
then
  sed -i -e "/int verbosity = /s/verbosity = .*$/verbosity = 5;/g" Selection_miniTree_${SampleName}.C
else
  sed -i -e "/int verbosity = /s/verbosity = .*$/verbosity = 0;/g" Selection_miniTree_${SampleName}.C
fi

# CREATING (AND COMPILING) ONE MACRO FOR EACH ${NumberOfIpnTreeFilesToRunInOneJob} number of files
if [ "${NumberOfJobs}" != "0" ]
then
  for i in `seq 0 ${NumberOfJobsMinus1}`
  do
	  echo "Preparing macro file ${i}..."
		let "begin=(i*NumberOfIpnTreeFilesToRunInOneJob)+1"
		let "end=((i+1)*NumberOfIpnTreeFilesToRunInOneJob)"
		sed -e "s/SAMPLEPART/${SampleName}_${i}/g" Selection_miniTree_${SampleName}.C > Selection_miniTree_${SampleName}_${i}${version}.C
		for ((j=0; j < ${NumberOfIpnTreeFilesToRunInOneJob} ; j++))
		do
		  file=`head -n 1 TEMP_FileList_${SampleName} | sed -e "s,\/,\\\/,g"`
		  runTreeLine=`echo "inputRunTree->Add(\"${file}\");"`
		  sed -i -e "/INSERTFILES/a\  ${runTreeLine}" Selection_miniTree_${SampleName}_${i}${version}.C
		  eventTreeLine=`echo "inputEventTree->Add(\"${file}\");"`
		  sed -i -e "/INSERTFILES/a\  ${eventTreeLine}" Selection_miniTree_${SampleName}_${i}${version}.C
		  sed -i -e "/INSERTFILES/a\  " Selection_miniTree_${SampleName}_${i}${version}.C
		  sed -i -e '1d' TEMP_FileList_${SampleName}
		done
		g++ Selection_miniTree_${SampleName}_${i}${version}.C -L${WORKINGDIR} -lToto `root-config --libs --cflags` -m32 -O2 -o Selection_miniTree_${SampleName}_${i}${version}
###### FOR TEST
#		break
###### FOR TEST
  done
fi
if [ "${rest}" != "0" ]
then
  i="$NumberOfJobs"
  echo "Preparing macro file ${i}..."
  let "begin=((i)*NumberOfIpnTreeFilesToRunInOneJob)+1"
  let "end=begin+rest-1"
  sed -e "s/SAMPLEPART/${SampleName}_${i}/g" Selection_miniTree_${SampleName}.C > Selection_miniTree_${SampleName}_${i}${version}.C
  for ((j=0; j < ${rest} ; j++))
  do
    file=`head -n 1 TEMP_FileList_${SampleName} | sed -e "s,\/,\\\/,g"`
    runTreeLine=`echo "inputRunTree->Add(\"${file}\");"`
    sed -i -e "/INSERTFILES/a\  ${runTreeLine}" Selection_miniTree_${SampleName}_${i}${version}.C
    eventTreeLine=`echo "inputEventTree->Add(\"${file}\");"`
    sed -i -e "/INSERTFILES/a\  ${eventTreeLine}" Selection_miniTree_${SampleName}_${i}${version}.C
    sed -i -e "/INSERTFILES/a\  " Selection_miniTree_${SampleName}_${i}${version}.C
    sed -i -e '1d' TEMP_FileList_${SampleName}
  done
  g++ Selection_miniTree_${SampleName}_${i}${version}.C -L${WORKINGDIR} -lToto `root-config --libs --cflags` -m32 -O2 -o Selection_miniTree_${SampleName}_${i}${version}
fi


# LOOP OVER PARAMETERS
#for parameter in `seq -w 0.95 0.001 1.00`
#for parameter in `seq -w 1.00 0.001 1.05`
#for parameter in `seq -w 0.95 0.001 1.05`
for parameter in `seq -w 0 0.1 10.0`
#for parameter in `echo "0.5"`
#for parameter in `echo "0.950"`
do
	RESULTSDIR=`echo "${WORKINGDIR}/Selected/${cutVersion}_${parameter}/${SampleName}"`
	if [[ ! -d Selected/${cutVersion}_${parameter} ]]
	then
		mkdir Selected/${cutVersion}_${parameter}
		echo -e "\tSelected/${cutVersion}_${parameter} CREATED"
	fi
	if [[ ! -d Selected/${cutVersion}_${parameter}/${SampleName} ]]
	then
		mkdir Selected/${cutVersion}_${parameter}/${SampleName}
		mkdir Selected/${cutVersion}_${parameter}/${SampleName}/lib
		mkdir Selected/${cutVersion}_${parameter}/${SampleName}/interface
		echo -e "\tSelected/${cutVersion}_${parameter}/${SampleName} CREATED"
	fi
	LOCATION=`echo "Selected/${cutVersion}_${parameter}/${SampleName}"`
	if [ "${NumberOfJobs}" != "0" ]
	then
	  for i in `seq 0 ${NumberOfJobsMinus1}`
	  do
			echo "Copy files to ${RESULTSDIR}"
			cp Selection_miniTree_${SampleName}_${i}${version} ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}_${parameter}${version}
			cp Selection_miniTree_${SampleName}_${i}${version}.C ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}_${parameter}${version}.C
			cp ${WORKINGDIR}/libToto.so ${RESULTSDIR}/
			cp ${WORKINGDIR}/libToto.so ${RESULTSDIR}/lib/
			cp ${WORKINGDIR}/interface/* ${RESULTSDIR}/interface/

	    echo "Preparing batch file ${i}..."
	    sed -e "s,EXEDIR,${RESULTSDIR},1" batch_template_DTM.sh > ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,MACRO,Selection_miniTree_${SampleName}_${i}_${parameter}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
			sed -i -e "s,SAMPLEPART,${SampleName}_${i},g" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
			sed -i -e "s,LOCATION,${LOCATION},g" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh

			echo "adding task to the list"
			echo "dtm-task-add -t ${parameter}-V05-FSR_${i} -c ${time} -m ${memory} -p ${prodName} -s ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh -a ${parameter}"
			dtm-task-add -t ${parameter}-V05-FSR_${i} -c ${time} -m ${memory} -p ${prodName} -s ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh -a ${parameter}
#### FOR TEST
#			break
#### FOR TEST
	  done
	fi
	if [ "${rest}" != "0" ]
	then
	  i="$NumberOfJobs"
			echo "Copy files to ${RESULTSDIR}"
			cp Selection_miniTree_${SampleName}_${i}${version} ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}_${parameter}${version}
			cp Selection_miniTree_${SampleName}_${i}${version}.C ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}_${parameter}${version}.C
			cp ${WORKINGDIR}/libToto.so ${RESULTSDIR}/
			cp ${WORKINGDIR}/libToto.so ${RESULTSDIR}/lib/
			cp ${WORKINGDIR}/interface/* ${RESULTSDIR}/interface/

		  echo "Preparing macro file ${i}..."
	    sed -e "s,EXEDIR,${RESULTSDIR},1" batch_template_DTM.sh > ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
	    sed -i -e "s,MACRO,Selection_miniTree_${SampleName}_${i}_${parameter}${version},1" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
			sed -i -e "s,SAMPLEPART,${SampleName}_${i},g" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh
			sed -i -e "s,LOCATION,${LOCATION},g" ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh

			echo "adding task to the list"
			echo "dtm-task-add -t ${parameter}-V05-FSR_${i} -c ${time} -m ${memory} -p ${prodName} -s ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh -a ${parameter}"
			dtm-task-add -t ${parameter}-V05-FSR_${i} -c ${time} -m ${memory} -p ${prodName} -s ${RESULTSDIR}/${SampleName}_${i}_${parameter}${version}_batch.sh -a ${parameter}
	fi

done # END OF LOOP OVER PARAMETERS

	if [ "${NumberOfJobs}" != "0" ]
	then
	  for i in `seq 0 ${NumberOfJobsMinus1}`
	  do
			rm Selection_miniTree_${SampleName}_${i}${version}
			rm Selection_miniTree_${SampleName}_${i}${version}.C
	  done
	fi
	if [ "${rest}" != "0" ]
	then
	  i="$NumberOfJobs"
		rm Selection_miniTree_${SampleName}_${i}${version} 
    rm Selection_miniTree_${SampleName}_${i}${version}.C
	fi


rm Selection_miniTree_${SampleName}.C
rm TEMP_FileList_${SampleName}


exit 0

