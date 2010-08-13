#!/bin/bash
# script to spot duplicate root files and print them
# Written by O. Bondu (August 2010)

syntax="${0} {sample}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi
sample=${1}
CRABdir=${sample}
ROOTFILESdir=${sample}

'ls' ${ROOTFILESdir}/*root > TEMPLIST_${sample}.txt
'ls' ${ROOTFILESdir}/*root | rev | cut -d _ -f 3 | rev > TEMP_${sample}.txt
previousFaulty=""
for number in `cat TEMP_${sample}.txt`
do
	count=`grep -w ${number} TEMP_${sample}.txt | wc -w`
	if [[ ${count} != 1  && ${number} != ${previousFaulty} ]]
	then
		if [[ ! -d ${ROOTFILESdir}/Duplicated ]]
		then
			mkdir ${ROOTFILESdir}/Duplicated
		fi
		echo "WARNING: there is two files corresponding to job # ${number}"
		TRUEFILE=`cat ${CRABdir}/res/crab_fjr_${number}.xml | grep "PFN Value=" | rev | cut -d / -f 2 | cut -d \" -f 2 | rev`
		echo -e "\tThe true file is:\t${TRUEFILE}"
		FALSEFILE=`grep "_${number}_" TEMPLIST_${sample}.txt | grep _${number}_[0-9]_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9].root | grep -v ${TRUEFILE} | rev | cut -d / -f 1 | rev`
		echo -e "\tThe false file is:\t${FALSEFILE}"
		echo -e "\t\tMoving the false file to ${ROOTFILESdir}/Duplicated/"
		mv ${ROOTFILESdir}/${FALSEFILE} ${ROOTFILESdir}/Duplicated/${FALSEFILE}
		previousFaulty=${number}
		echo ""
	fi
done

if [[ ${previousFaulty} == "" ]]
then
	echo "There is NO duplicated files in the directory ${ROOTFILESdir}"
fi

rm TEMP_${sample}.txt
rm TEMPLIST_${sample}.txt

exit 0
