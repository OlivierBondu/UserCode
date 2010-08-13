#!/bin/bash
# Script to write out the multicrab chnges for each part
# Written by O. Bondu (July 2010)

syntax="Syntax ${0} {partX}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

partX=${1}
JSONrunlist=`echo "JSON_runlist_${partX}.txt"`
user_remote_dir=`cat crab_${partX}.cfg | grep user_remote_dir | grep IpnTree | awk '{print $3}'`
ui_working_dir=`cat crab_${partX}.cfg | grep ui_working_dir | grep IpnTree | awk '{print $3}'`
runselection=`cat crab_${partX}.cfg | grep runselection | awk '{print $3}' | sed -e "s/-/ /g"`
runMIN=`echo ${runselection} | awk '{print $1}'`
runMAX=`echo ${runselection} | awk '{print $2}'`

echo "[MULTICRAB]" > multicrab_${partX}.cfg
echo "cfg=../crab_${partX}.cfg" >> multicrab_${partX}.cfg
echo "" >> multicrab_${partX}.cfg

if [[ ! -e ${partX} ]]
then
	mkdir ${partX}
	ln -s ../multicrab_${partX}.cfg ${partX}/multicrab.cfg
fi


for run in `cat ${JSONrunlist}`
do
	if [[ ${run} -lt "${runMIN}" ]]
	then
#		echo "${run} below range ${runMIN}-${runMAX}"
		continue
	fi
	if [[ ${run} -gt "${runMAX}" ]]
	then
#		echo "${run} above range ${runMIN}-${runMAX}"
		continue
	fi
#	echo "${run} in range ${runMIN}-${runMAX}"
	echo "[${partX}__run_${run}]" >> multicrab_${partX}.cfg
	echo "CMSSW.runselection = ${run}" >> multicrab_${partX}.cfg
	echo "USER.user_remote_dir = ${partX}__run_${run}" >> multicrab_${partX}.cfg
	echo "USER.ui_working_dir = ${partX}__run_${run}" >> multicrab_${partX}.cfg
	echo ""  >> multicrab_${partX}.cfg
	if [[ ! -e ${partX}/${partX}__run_${run} ]]
	then
		mkdir ${partX}/${partX}__run_${run}
	fi
done

exit 0
