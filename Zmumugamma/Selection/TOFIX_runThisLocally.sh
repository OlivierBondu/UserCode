#!/usr/local/bin/bash
echo "*********************"
echo "*** ${1} SAMPLE***"
echo "*********************"

HOME=/afs/in2p3.fr/home/o/obondu

if [ "${1}" = "" ]
then
    echo "ERROR : correct syntax is : runThisLocally.sh {sample name}"
    exit
else
		SampleName=${1}
fi

SAMPLES=/sps/cms/obondu/CMSSW_3_5_7/src/Zmumugamma/RecoSamples/${SampleName}
NumberOfFiles=`ls $SAMPLES/Toto_${SampleName}_*.root | wc -l`

echo "Number of input files : $NumberOfFiles"
if [ "${NumberOfFiles}" = "0" ]
    then echo "ERROR : No input file"
    exit
fi


echo "Cleaning working area..."
rm -f ${SampleName}
stew="false"
if [ "${SampleName}" = "Zmumugamma" ]
	then
		signal="true"
		zjetveto="false"
	else
		signal="false"
##################################
## TEMPORARY
##################################
		zjetveto="false"		
fi
	
begin=0
end=`echo "${NumberOfFiles} -1" | bc`

echo "Preparing macro file..."
sed -e "s,OUTPUT.root,Selected/${SampleName}/Selected_${SampleName}.root,1" ClemFilter.C > Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s,RESULTS.txt,Selected/${SampleName}/Results_${SampleName}.txt,1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/ISSIGNAL/${signal}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/ISSTEW/${stew}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/IS_ZJETS_VETO/${zjetveto}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/BEGINFILENUMBER/${begin}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/ENDFILENUMBER/${end}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C
sed -i -e "s/SAMPLEPART/${SampleName}/1" Selected/${SampleName}/ClemFilter_${SampleName}.C

echo "Set environment"
export HOMEDIR=/afs/in2p3.fr/home/o/obondu
export CMSSWDIR=/afs/in2p3.fr/home/o/obondu/scratch/CMSSW_3_5_7/src
export WORKDIR=/afs/in2p3.fr/home/o/obondu/scratch/CMSSW_3_5_7/src/Zmumugamma/Selection/
cd $CMSSWDIR

source $HOMEDIR/.envCMS_3_5_7_ANA.sh

cd $CMSSWDIR
echo "Runnig eval scramv1"
eval `scramv1 ru -sh`

cd $WORKDIR
echo "Running actual job"
root -l -b -q Selected/${SampleName}/ClemFilter_${SampleName}.C 2> Selected/${SampleName}/local_${SampleName}_err.log | tee > Selected/${SampleName}/local_${SampleName}_out.log  


exit
