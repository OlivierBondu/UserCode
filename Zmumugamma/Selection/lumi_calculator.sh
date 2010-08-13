#!/bin/bash
# Script to compute run by run lumi (for each run for each part), write it to file, then compute the summed values
# Written by O.Bondu (July 2010)

syntax="Syntax ${0} {partX}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

partX=${1}

echo "**********************************************" > lumi_${partX}.txt
echo "*** TOTAL LUMI COMPUTED FOR ${partX} ****" >> lumi_${partX}.txt
echo "**********************************************" >> lumi_${partX}.txt

for run in `'ls' ${partX} | grep ${partX}__`
#for run in `echo "partI__run_135149"`
do
	echo "*******************************************************" >> lumi_${partX}.txt
	echo "${run}" >> lumi_${partX}.txt
	echo "${run}"
	if [[ ! -e ${partX}/${run}/res/all ]]
	then
		mkdir ${partX}/${run}/res/all
	fi
	cp ${partX}/${run}/res/CMSSW_*.stdout ${partX}/${run}/res/all
	for stdoutFolder in `'ls' ${partX}/${run}/res | grep Submission_`
	do
		echo "copy files from ${stdoutFolder} to all"
		cp ${partX}/${run}/res/${stdoutFolder}/CMSSW_*.stdout ${partX}/${run}/res/all
	done
	totalProcessed=`cat ${partX}/${run}/res/all/CMSSW_*stdout | grep "Total number of events"| awk --field-separator ": " 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
	echo "Total number of events: ${totalProcessed}" >> lumi_${partX}.txt
	lumiCalc.py -c frontier://LumiProd/CMS_LUMI_PROD --nowarning -i ${partX}/${run}/res/lumiSummary.json overview >> lumi_${partX}.txt
	echo ""
done

totalLumi=`cat lumi_${partX}.txt | grep -A 3 Total | grep "|" | grep -v Selected | awk 'BEGIN {SUM=0} {SUM+=$8} END {print SUM}'`
GrandTotalProcessed=`cat lumi_${partX}.txt | grep "Total number of events"| awk --field-separator ": " 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
echo -e "\n\n\nTOTAL LUMI = ${totalLumi} (/mu b)" >> lumi_${partX}.txt
echo -e "Grand Total number of events: ${GrandTotalProcessed}" >> lumi_${partX}.txt
echo -e "\n\n\nTOTAL LUMI = ${totalLumi} (/mu b)"
echo -e "Grand Total number of events: ${GrandTotalProcessed}"
echo ""
echo "Detailed results are in lumi_${partX}.txt"




exit 0
