#!/usr/local/bin/bash
# Small script to run the selection code on the anastasie CC IN2P3 batch cluster
# Written by Olivier Bondu (January 2010) for CMSSW 3_1_4
CMSSWversion=CMSSW_3_5_8_patch3

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

NumberOfFiles=`ls ${RECODIR}/${SampleName}/Toto_${SampleName}_*.root | wc -l`
RawSampleName=`echo ${SampleName} | cut -d _ -f 2-`
Energy=`echo ${SampleName} | cut -d _ -f -1`
RESULTSDIR=`echo "${WORKINGDIR}/Selected/${cutVersion}/${SampleName}"`

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
if [ "${SampleName}" = "3" ]
    then
	stew="true"
    else
	stew="false"
fi

sample=`echo ${RawSampleName} | grep "alpgen" |rev| cut -d _ -f 2-|rev`

if [ "${RawSampleName}" = "ZJets-madgraph" ]
	then
		zjetveto="true"
elif [ "${RawSampleName}" = "Z_0jet-alpgen" ]
	then
    zjetveto="true"
elif [ "${sample}" = "Z_1jet" ]
	then
    zjetveto="true"
elif [ "${sample}" = "Z_2jet" ]
then
    zjetveto="true"
elif [ "${sample}" = "Z_3jet" ]
then
    zjetveto="true"
elif [ "${sample}" = "Z_4jet" ]
then
    zjetveto="true"
elif [ "${sample}" = "Z_5jet" ]
then
    zjetveto="true"
else
	zjetveto="false"
fi

rm -f ${SampleName}${version}*
memory="1024MB"
time=4286000
queue=T
begin=1

SizeOfSamples=3

let "NumberOfJobs=NumberOfFiles/SizeOfSamples"
let "NumberOfJobsMinus1=NumberOfJobs-1"
#echo "NUMBER OF JOBS : $NumberOfJobs"
let "rest=NumberOfFiles-SizeOfSamples*NumberOfJobs"
#echo "REST : $rest"
#echo ""


echo "Preparing pre-macro file..."
sed -e "s/ISSIGNAL/${signal}/1" ${versionpath}ClemFilter${version}.C > ClemFilter_${SampleName}.C
sed -i -e "s/ISSTEW/${stew}/1" ClemFilter_${SampleName}.C
sed -i -e "s/IS_ZJETS_VETO/${zjetveto}/1" ClemFilter_${SampleName}.C
sed -i -e "s/SAMPLEPART/${SampleName}/1" ClemFilter_${SampleName}.C

if [ "${NumberOfJobs}" != "0" ]
then
    for i in `seq 0 ${NumberOfJobsMinus1}`
    do
	echo "Preparing macro file ${i}..."
	let "begin=(i*SizeOfSamples)+1"
	let "end=((i+1)*SizeOfSamples)"
#    echo -e "BEGIN : $begin \t END : $end"
        sed -e "s,OUTPUT.root,${RESULTSDIR}/Selected_${SampleName}_${i}${version}.root,1" ClemFilter_${SampleName}.C > ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
        sed -i -e "s,RESULTS.txt,${RESULTSDIR}/Results_${SampleName}_${i}${version}.txt,1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
        sed -i -e "s/BEGINFILENUMBER/${begin}/1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
        sed -i -e "s/ENDFILENUMBER/${end}/1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
    
	echo "Preparing batch file..."
        sed -e "s/NAME/${RawSampleName}_${i}${version}/1" batch_template.sh > ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
        sed -i -e "s,MACRO,${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
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
    let "begin=((i)*SizeOfSamples)+1"
    let "end=begin+rest-1"
#echo -e "BEGIN : $begin \t END : $end"
    sed -e "s,OUTPUT.root,${RESULTSDIR}/Selected_${SampleName}_${i}${version}.root,1" ClemFilter_${SampleName}.C > ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
    sed -i -e "s,RESULTS.txt,${RESULTSDIR}/Results_${SampleName}_${i}${version}.txt,1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
    sed -i -e "s/BEGINFILENUMBER/${begin}/1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C
    sed -i -e "s/ENDFILENUMBER/${end}/1" ${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version}.C

    echo "Preparing batch file..."
    sed -e "s/NAME/${RawSampleName}_${i}${version}/1" batch_template.sh > ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,OUTLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,ERRLOG,${RESULTSDIR}/${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s,MACRO,${RESULTSDIR}/ClemFilter_${SampleName}_${i}${version},1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/TIME/${time}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/QUEUE/${queue}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
    sed -i -e "s/MEMORY/${memory}/1" ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh

    echo "Submitting job..."
    qsub ${RESULTSDIR}/${SampleName}_${i}${version}_batch.sh
fi


rm ClemFilter_${SampleName}.C

exit
