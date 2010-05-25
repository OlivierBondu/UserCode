#!/usr/local/bin/bash
# Script to fetch cut informations
# Created by Olivier Bondu for CMSSW_1_6_12
# Modified for 336 (January 2010)

CMSSW_release="CMSSW_3_5_8_patch3"

syntax="${0} {SelectionVersion}"

if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi
SelectionVersion=${1}
SELECTEDDIR=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/Selection/Selected/${SelectionVersion}

echo "*** RawSelectionCutsNumbers_${SelectionVersion}.txt ***"

rm RawSelectionCutsNumbers_${SelectionVersion}.txt
echo -e "*** RAW RESULTS ***" > RawSelectionCutsNumbers_${SelectionVersion}.txt
echo -e "Sample (files)\t0\tCSA07ID\tZJETVETO\t1.a\t1.b\t1.c\t1.d\t1.e\t2.a\t2.b\t2.c\t3\t4\t5\t6\t7\t8\t9\t10" >> RawSelectionCutsNumbers_${SelectionVersion}.txt
echo "" >> RawSelectionCutsNumbers_${SelectionVersion}.txt

NB=`'ls' ${SELECTEDDIR} | wc -l`
echo "Processing .out files"
for sample in `'ls' ${SELECTEDDIR}`
do
#				break
#	echo "Treating ${sample}..."
	for file in `'ls' ${SELECTEDDIR}/${sample} | grep ${sample}_ | grep _${SelectionVersion}.out`
	do
		SAMPLEandNb=`echo ${file} | cut -d . -f -1 | rev | cut -d _ -f 2- | rev`
		NbOfFiles=`grep "Using" ${SELECTEDDIR}/${sample}/${file} | awk '{print $2}'`
	  total=`grep "Number of events total" ${SELECTEDDIR}/${sample}/${file} | awk '{print $6}'`
	  csa07id=`grep "Number of events after CSA07ID" ${SELECTEDDIR}/${sample}/${file} | awk '{print $7}'`
	  zjetveto=`grep "Number of events after Z+Jets veto" ${SELECTEDDIR}/${sample}/${file} | awk '{print $8}'`
	  allcuts=""
	  allcuts="${allcuts}\t${total}\t${csa07id}\t${zjetveto}"
	  for cutvalue in `grep "Number of events after cut" ${SELECTEDDIR}/${sample}/${file} | awk '{print $8}'`
	  do
      allcuts="${allcuts}\t${cutvalue}"
	  done
	  if [ "${SAMPLEandNb}" != "7TeV_Zmumugamma" ]
	  then
			if [ "${SAMPLEandNb}" != "7TeV_Zmumugamma_10GeV" ]
			then
			  cutvalue=`echo "scale=1 ; $cutvalue/5.0" |bc -l`
			  allcuts="${allcuts}\t${cutvalue}"
			fi
	  fi
		# echo -e "${SAMPLEandNb}\t( ${NbOfFiles} )${allcuts}"
		echo -e  "${SAMPLEandNb}\t( ${NbOfFiles} )${allcuts}" >> TEMPRESULTS_${SelectionVersion}.txt
		NbOfFiles=""
		total=""
		csa07id=""
		allcuts=""
		cutvalue=""																								
		done # end of loop over sample files
#		break
done # end of loop over samples
#exit 4

echo ""
echo "Merging splitted results..."

for sample in `'ls' ${SELECTEDDIR}`
do
	cols=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}_0" | wc -w`
  SubFiles=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | grep -v "${sample}_10GeV" | wc -l`
  NbOfFiles=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | grep -v "${sample}_10GeV" | awk 'BEGIN {NbOfFiles=0} {NbOfFiles+=$3} END {print NbOfFiles}'`
  allcuts=""
#	echo "$cols $SubFiles $NbOfFiles"
  for currentColumn in `seq 5 $cols`
  do
		currentSum=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | grep -v "${sample}_10GeV" | awk 'BEGIN {SUM=0} {SUM+=$'"${currentColumn}"'} END {print SUM}'`
		allcuts="${allcuts}\t${currentSum}"
  done
	if [[ `echo ${sample} | grep 7TeV_Zmumugamma` ]]
	then
		if [[ `echo ${sample} | grep 7TeV_Zmumugamma_10GeV` ]]
		then
			cat TEMPRESULTS_${SelectionVersion}.txt | grep -v "${sample}" > TEMPRESULTSBIS_${SelectionVersion}.txt
		else
			cat TEMPRESULTS_${SelectionVersion}.txt | grep -v "${sample}" > TEMPRESULTSBIS_${SelectionVersion}.txt
			cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}_10GeV" >> TEMPRESULTSBIS_${SelectionVersion}.txt
		fi
	else
		cat TEMPRESULTS_${SelectionVersion}.txt | grep -v "${sample}" > TEMPRESULTSBIS_${SelectionVersion}.txt
	fi
  echo -e "${sample}\t(${NbOfFiles})${allcuts}" >> TEMPRESULTSBIS_${SelectionVersion}.txt
  echo "${SubFiles} SubFiles of ${sample} merged"
  mv TEMPRESULTSBIS_${SelectionVersion}.txt TEMPRESULTS_${SelectionVersion}.txt
#	break
done # end of loop over samples

cat TEMPRESULTS_${SelectionVersion}.txt | sort >> RawSelectionCutsNumbers_${SelectionVersion}.txt

rm TEMPRESULTS_${SelectionVersion}.txt

echo ""
echo "All results are in RawSelectionCutsNumbers_${SelectionVersion}.txt"

exit 0


##################################
##### OLD STUFF ##################
##################################
for file in `ls -l  ${SelectionVersion} | grep ${SelectionVersion} | grep ".out" | awk '{print $9}'`
do
#	echo ${file}
if [ "${SelectionVersion}" != "." ]
  then
		SAMPLEandNb=`echo ${file} | cut -d . -f -1 | rev | cut -d _ -f 2- | rev` 
	else
		SAMPLEandNb=`echo ${file} | cut -d . -f -1 | rev | cut -d _ -f 1- | rev`
fi
#	echo ${SAMPLEandNb}
	NbOfFiles=`grep "Using" ${SELECTEDDIR}/${sample}/${file} | awk '{print $2}'`
	total=`grep "Number of events total" ${SELECTEDDIR}/${sample}/${file} | awk '{print $6}'`
	csa07id=`grep "Number of events after CSA07ID" ${SELECTEDDIR}/${sample}/${file} | awk '{print $7}'`
	zjetveto=`grep "Number of events after Z+Jets veto" ${SELECTEDDIR}/${sample}/${file} | awk '{print $8}'`
	allcuts=""
	allcuts="${allcuts}\t${total}\t${csa07id}\t${zjetveto}"
	for cutvalue in `grep "Number of events after cut" ${SELECTEDDIR}/${sample}/${file} | awk '{print $8}'`
	do
	    allcuts="${allcuts}\t${cutvalue}"
	done
	if [ "${SAMPLEandNb}" != "SIGNAL_0" ]
	  then
			cutvalue=`echo "scale=1 ; $cutvalue/5.0" |bc -l`
			allcuts="${allcuts}\t${cutvalue}"
	fi
#	echo -e "${SAMPLEandNb}\t( ${NbOfFiles} )${allcuts}"
	echo -e  "${SAMPLEandNb}\t( ${NbOfFiles} )${allcuts}" >> TEMPRESULTS_${SelectionVersion}.txt
	NbOfFiles=""
	total=""
	csa07id=""
	allcuts=""
	cutvalue=""
done #end of loop over files

#exit

echo ""
echo "Merging splitted results..."
#splittedSample=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "_0" | awk '{print $1}'| rev | cut -d _ -f 2- | rev`
if [ "${SelectionVersion}" != "." ]
	then
		splittedSample=`'ls' -l  ${SelectionVersion} | grep "_0_${SelectionVersion}.out" | awk '{print $9}'| cut -d . -f -1 | rev | cut -d _ -f 3- | rev`
	else
		splittedSample=`'ls' -l | grep "_0.out" | awk '{print $9}'| cut -d . -f -1 | rev | cut -d _ -f 2- | rev`
fi
echo ${splittedSample}

for sample in ${splittedSample}
do
	cols=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}_0" | wc -w`
  SubFiles=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | wc -l`
  NbOfFiles=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | awk 'BEGIN {NbOfFiles=0} {NbOfFiles+=$3} END {print NbOfFiles}'`
  allcuts=""
  for currentColumn in `seq 5 $cols`
  do
		currentSum=`cat TEMPRESULTS_${SelectionVersion}.txt | grep "${sample}" | awk 'BEGIN {SUM=0} {SUM+=$'"${currentColumn}"'} END {print SUM}'`
		allcuts="${allcuts}\t${currentSum}"
  done
  cat TEMPRESULTS_${SelectionVersion}.txt | grep -v "${sample}" > TEMPRESULTSBIS_${SelectionVersion}.txt
  echo -e "${sample}\t( ${NbOfFiles} )${allcuts}" >> TEMPRESULTSBIS_${SelectionVersion}.txt
  echo "${SubFiles} SubFiles of ${sample} merged"
  mv TEMPRESULTSBIS_${SelectionVersion}.txt TEMPRESULTS_${SelectionVersion}.txt
done

cat TEMPRESULTS_${SelectionVersion}.txt | sort >> RawSelectionCutsNumbers_${SelectionVersion}.txt

rm TEMPRESULTS_${SelectionVersion}.txt

echo ""
echo "All results are in RawSelectionCutsNumbers_${SelectionVersion}.txt"


