#!/usr/local/bin/bash
# Small script to run the selection code on the anastasie CC IN2P3 batch cluster
# Written by Olivier Bondu (January 2010) for CMSSW 3_1_4
CMSSWversion=CMSSW_3_6_1_patch4

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
#Uncomment the line below if the sample's name contain _alpgen or _madgraph, etc.
#RawSampleName=`echo ${SampleName} | cut -d _ -f 2-`
RawSampleName=`echo ${SampleName}`
#Energy=`echo ${SampleName} | cut -d _ -f -1`
RESULTSDIR=`echo "${WORKINGDIR}/Selected/${cutVersion}/${SampleName}"`

echo "*********************************************"
echo "*********************************************"
echo "*** Sample ${SampleName} version ${cutVersion}"
echo "*********************************************"
echo "*********************************************"

echo "Number of input files : $NumberOfFiles"
if [ "${NumberOfFiles}" = "0" ]
    then echo "ERROR : No input file"
    exit 2
fi

echo "Cleaning working area and setting parameters..."
echo ${SampleName} | grep "Zmumugamma" &> /dev/null
if [ ${?} = 0 ]
then
	signal="true"
else 
	signal="false"
# **********************************
# *** WARNING ! just for test !! ***
# **********************************
#	echo "WARNING : BACKGROUND passed as SIGNAL !!"
#	signal="true"
# **********************************
# *** WARNING ! just for test !! ***
# **********************************
fi

if [ "${SampleName}" = "QCD_Pt15" ]
then
	minPtHat="15"
	maxPtHat="30"
elif [ "${SampleName}" = "QCD_Pt30" ]
then
  minPtHat="30"
  maxPtHat="80"
elif [ "${SampleName}" = "QCD_Pt80" ]
then
  minPtHat="80"
  maxPtHat="170"
elif [ "${SampleName}" = "QCD_Pt170" ]
then
  minPtHat="170"
  maxPtHat="300"
elif [ "${SampleName}" = "QCD_Pt300" ]
then
  minPtHat="300"
  maxPtHat="1000000"
elif [ "${SampleName}" = "PhotonJet_Pt15" ]
then
  minPtHat="15"
  maxPtHat="30"
elif [ "${SampleName}" = "PhotonJet_Pt30" ]
then
  minPtHat="30"
  maxPtHat="80"
elif [ "${SampleName}" = "PhotonJet_Pt80" ]
then
  minPtHat="80"
  maxPtHat="170"
elif [ "${SampleName}" = "PhotonJet_Pt170" ]
then
  minPtHat="170"
  maxPtHat="300"
elif [ "${SampleName}" = "PhotonJet_Pt300" ]
then
  minPtHat="300"
  maxPtHat="470"
elif [ "${SampleName}" = "PhotonJet_Pt470" ]
then
  minPtHat="470"
  maxPtHat="1000000"
else
	minPtHat="-100"
	maxPtHat="1000000"
fi

echo "${SampleName}" | grep part > /dev/null
if [ "$?" = "0" ]
then
	verbosity="on"
else
	verbosity="off"
fi

if [ "${SampleName}" = "ZmumuJet_Pt0to15" ]
then
	zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt15to20" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt20to30" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt30to50" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt50to80" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt80to120" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt120to170" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt170to230" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt230to300" ]
then
  zjetveto="true"
elif [ "${SampleName}" = "ZmumuJet_Pt300toInf" ]
then
  zjetveto="true"
else
	zjetveto="false"
fi



stew="false"


rm -f ${SampleName}${version}*
memory="1024MB"
time=4286000
queue=T
begin=1

NumberOfIpnTreeFilesToRunInOneJob=50

let "NumberOfJobs=NumberOfFiles/NumberOfIpnTreeFilesToRunInOneJob"
let "NumberOfJobsMinus1=NumberOfJobs-1"
#echo "NUMBER OF JOBS : $NumberOfJobs"
let "rest=NumberOfFiles-NumberOfIpnTreeFilesToRunInOneJob*NumberOfJobs"
#echo "REST : $rest"
#echo ""

echo "Preparing pre-macro file..."
sed -e "s/signal = false/signal = ${signal}/1" ${versionpath}Selection_miniTree${version}.C > Selection_miniTree_${SampleName}.C
sed -i -e "s/stew = false/stew = ${stew}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/zjet_veto = false/zjet_veto = ${zjetveto}/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/minPtHat = -100;/minPtHat = ${minPtHat};/1" Selection_miniTree_${SampleName}.C
sed -i -e "s/maxPtHat = 1000000;/maxPtHat = ${maxPtHat};/1" Selection_miniTree_${SampleName}.C
if [ "${verbosity}" = "on" ]
then
	sed -i -e "/int verbosity = /s/verbosity = .*$/verbosity = 5;/g" Selection_miniTree_${SampleName}.C
else
	sed -i -e "/int verbosity = /s/verbosity = .*$/verbosity = 0;/g" Selection_miniTree_${SampleName}.C
fi

#exit 1

if [ "${NumberOfJobs}" != "0" ]
then
    for i in `seq 0 ${NumberOfJobsMinus1}`
    do
	echo "Preparing macro file ${i}..."
	let "begin=(i*NumberOfIpnTreeFilesToRunInOneJob)+1"
	let "end=((i+1)*NumberOfIpnTreeFilesToRunInOneJob)"
#    echo -e "BEGIN : $begin \t END : $end"
				sed -e "s/SAMPLEPART/${SampleName}_${i}/g" Selection_miniTree_${SampleName}.C > ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
#        sed -i -e "s,RESULTS.txt,${RESULTSDIR}/Results_${SampleName}_${i}${version}.txt,1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
 #       sed -i -e "s/BEGINFILENUMBER/${begin}/1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
#        sed -i -e "s/ENDFILENUMBER/${end}/1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C

	for ((j=0; j < ${NumberOfIpnTreeFilesToRunInOneJob} ; j++))
	do
		file=`head -n 1 TEMP_FileList_${SampleName} | sed -e "s,\/,\\\/,g"`
		runTreeLine=`echo "inputRunTree->Add(\"${file}\");"`
#		echo ${runTreeLine}
		sed -i -e "/INSERTFILES/a\  ${runTreeLine}" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
		eventTreeLine=`echo "inputEventTree->Add(\"${file}\");"`
#		echo ${eventTreeLine}
		sed -i -e "/INSERTFILES/a\  ${eventTreeLine}" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
		sed -i -e "/INSERTFILES/a\  " ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
		sed -i -e '1d' TEMP_FileList_${SampleName} 
	done

	g++ ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C `root-config --libs --cflags` -m32 -o ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}

    
	echo "Preparing batch file..."
        sed -e "s/NAME/${RawSampleName}_${i}${version}/1" batch_template.sh > ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
				sed -i -e "s,EXEDIR,${RESULTSDIR},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,MACRO,Selection_miniTree_${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s/TIME/${time}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s/QUEUE/${queue}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s/MEMORY/${memory}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
	
	echo "Submitting job..."
        qsub ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    done
fi

if [ "${rest}" != "0" ]
then
    i="$NumberOfJobs"
    echo "Preparing macro file ${i}..."
    let "begin=((i)*NumberOfIpnTreeFilesToRunInOneJob)+1"
    let "end=begin+rest-1"
#echo -e "BEGIN : $begin \t END : $end"
		sed -e "s/SAMPLEPART/${SampleName}_${i}/g" Selection_miniTree_${SampleName}.C > ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
#    sed -i -e "s,RESULTS.txt,${RESULTSDIR}/Results_${SampleName}_${i}${version}.txt,1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
#    sed -i -e "s/BEGINFILENUMBER/${begin}/1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
#    sed -i -e "s/ENDFILENUMBER/${end}/1" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C

  for ((j=0; j < ${rest} ; j++))
  do
    file=`head -n 1 TEMP_FileList_${SampleName} | sed -e "s,\/,\\\/,g"`
    runTreeLine=`echo "inputRunTree->Add(\"${file}\");"`
#   echo ${runTreeLine}
    sed -i -e "/INSERTFILES/a\  ${runTreeLine}" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
    eventTreeLine=`echo "inputEventTree->Add(\"${file}\");"`
#   echo ${eventTreeLine}
    sed -i -e "/INSERTFILES/a\  ${eventTreeLine}" ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
    sed -i -e "/INSERTFILES/a\  " ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C
    sed -i -e '1d' TEMP_FileList_${SampleName}
  done

	g++ ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}.C `root-config --libs --cflags` -m32 -o ${RESULTSDIR}/Selection_miniTree_${SampleName}_${i}${version}

    echo "Preparing batch file..."
    sed -e "s/NAME/${RawSampleName}_${i}${version}/1" batch_template.sh > ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
		sed -i -e "s,EXEDIR,${RESULTSDIR},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,MACRO,Selection_miniTree_${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/TIME/${time}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/QUEUE/${queue}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/MEMORY/${memory}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh

    echo "Submitting job..."
    qsub ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
fi


rm Selection_miniTree_${SampleName}.C
rm TEMP_FileList_${SampleName}

exit
