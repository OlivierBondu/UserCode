#!/bin/bash
# Script to extract information from the output of all fits
# Written by Olivier Bondu (August 2011)

syntax="$0 {outputPrefix}"
if [[ -z $1 ]]
then
	echo ${syntax}
	return 1
fi

outputPrefix="${1}"
#inputfile="VGamma_875pb-1_v2.out"
inputfile="fits_S6_2011_40_80.eo"


if [[ -e ${outputPrefix}_s_DATA.out ]]
then
	echo "ERROR: file already exists"
	return 2;
fi

for estimator in `echo "s f"`
do
	if [[ "${estimator}" == "f" ]]
	then
		var="))"
	elif [[ "${estimator}" == "s" ]]
	then
		var="s"
	fi
	for data in `echo "DATA MC"`
	do
echo "#################################################"
echo "### Processing ${estimator} ${data} ###"
echo "#################################################"
		for EBEE in `echo "EB EE"`
		do
#			for r9 in `echo "lowR9 highR9 inclusiveR9"`
			for r9 in `echo "lowR9 highR9"`
			do
#				for pt in `echo "10_lt_pt_lt_15 15_lt_pt_lt_20 20_lt_pt_lt_30 30_lt_pt_lt_inf inclusive_pt"`
				for pt in `echo "10_lt_pt_lt_12 12_lt_pt_lt_15 15_lt_pt_lt_20 20_lt_pt_lt_25 25_lt_pt_lt_30 30_lt_pt_lt_inf inclusivept"`
#				for pt in `echo "10_lt_pt_lt_12 12_lt_pt_lt_15 15_lt_pt_lt_20 20_lt_pt_lt_25 25_lt_pt_lt_30 30_lt_pt_lt_inf"`
				do
					if [[ "${pt}" == "inclusivept" ]]
					then
						list="160431_lt_run_lt_163869 165071_lt_run_lt_165970 165971_lt_run_lt_166502 166503_lt_run_lt_166861 166862_lt_run_lt_166967 inclusive_run"
					else
						list="inclusive_run"
					fi
#					for run in `echo "160431_lt_run_lt_163869 165071_lt_run_lt_165970 165971_lt_run_lt_166502 166503_lt_run_lt_166861 166862_lt_run_lt_166967 inclusive_run"`
# 				for run in `echo "inclusive_run"`
					for run in `echo "${list}"`
					do
						sample=`echo "${EBEE}_tight-${r9}--${pt}--${run}"`
#						echo ${sample}
	#					cat ${inputfile} | grep "${EBEE}_tight-${r9}--${pt}--${run}.*f = (1/(1+s))"					
	#					line=`grep -A 6 "${EBEE}_tight-${r9}--${pt}--${run}.*f = (1/(1+s))" ${inputfile} | grep "data - mc" | grep -v "(%)"`
						if [[ "${data}" == "DATA" ]]
						then
#							line=`grep -A 2 "${EBEE}_tight-${r9}--${pt}--${run}.*${var}\*" ${inputfile} | grep "data" | grep -v "(%)"`
#							f=`echo ${line} | awk '{print $4}'`
#							deltaf=`echo ${line} | awk '{print $6}'`
							line=`grep -A 2 "${EBEE}_tight-${r9}--${pt}--${run}.*${var}\*" ${inputfile} | grep "data" | grep "(%)"`
							f=`echo ${line} | awk '{print $5}'`
#							deltaf=`echo ${line} | awk '{print $7}'`
							deltaf=`echo ${line} | awk '{print $9}'` #sigma
						elif [[ "${data}" == "MC" ]]
						then
#							line=`grep -A 4 "${EBEE}_tight-${r9}--${pt}--${run}.*${var}\*" ${inputfile} | grep "mc" | grep -v "(%)"`
#							f=`echo ${line} | awk '{print $4}'`
#							deltaf=`echo ${line} | awk '{print $6}'`
							line=`grep -A 4 "${EBEE}_tight-${r9}--${pt}--${run}.*${var}\*" ${inputfile} | grep "mc" | grep "(%)"`
							f=`echo ${line} | awk '{print $5}'`
							deltaf=`echo ${line} | awk '{print $7}'`
							deltaf=`echo ${line} | awk '{print $9}'` #sigma
						fi
	#					line=`grep -A 2 "${EBEE}_tight-${r9}--${pt}--${run}.*f = (1/(1+s))" ${inputfile} | grep "data" | grep -v "(%)"`
	#					f=`echo ${line} | awk '{print $6}'`
	#					deltaf=`echo ${line} | awk '{print $8}'`
						line=`echo -e "${sample}\t${f}\t${deltaf}"`
						echo ${line}
						line=`echo "${line}" | sed -e "s/EB_tight-/0\t/g" -e "s/EE_tight-/1\t/g"`
						line=`echo "${line}" | sed -e "s/lowR9--/0\t/g" -e "s/highR9--/1\t/g" -e "s/inclusiveR9--/2\t/g"`
						line=`echo "${line}" | sed -e "s/10_lt_pt_lt_12--/0\t/g" -e "s/12_lt_pt_lt_15--/1\t/g" -e "s/15_lt_pt_lt_20--/2\t/g" -e "s/20_lt_pt_lt_25--/3\t/g" -e "s/25_lt_pt_lt_30--/4\t/g" -e "s/30_lt_pt_lt_inf--/5\t/g" -e "s/inclusivept--/6\t/g"`
#						line=`echo "${line}" | sed -e "s/10_lt_pt_lt_11--/0\t/g" -e "s/11_lt_pt_lt_12--/1\t/g" -e "s/12_lt_pt_lt_13--/2\t/g" -e "s/13_lt_pt_lt_14--/3\t/g" -e "s/14_lt_pt_lt_15--/4\t/g"`
						line=`echo "${line}" | sed -e "s/160431_lt_run_lt_163869/0\t/g" -e "s/165071_lt_run_lt_165970/1\t/g" -e "s/165971_lt_run_lt_166502/2\t/g" -e "s/166503_lt_run_lt_166861/3\t/g" -e "s/166862_lt_run_lt_166967/4\t/g" -e "s/inclusive_run/5\t/g"`
						echo ${line} >> ${outputPrefix}_${estimator}_${data}.out
					done
	#					return 1
				done
			done
		done
	done	
done

return 0
