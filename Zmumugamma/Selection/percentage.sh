#!/usr/local/bin/bash
# Script for comuting efficiencies on raw numbers for the selection
# Written by Olivier Bondu for CMSSW_1_6_12

if [ "${1}" = "" ]
then
    echo "You should put the version of the Analysis as an argument"
    exit
elif [ "${1}" = "CLEM" ]
then
    FILENAME=CLEMRESULTS_.txt
    totalawk=2
else
    FILENAME=RawSelectionCutsNumbers_${1}.txt
    totalawk=3
fi

echo "*******************************************************"
echo "*** Computing of relative and absolute efficiencies ***"
echo "*******************************************************"

echo "Removing old CUT_${1}.txt file"
rm CUT_${1}.txt

echo "Processing file ${FILENAME} ..."
echo "`head -3 ${FILENAME}`" > CUT_${1}.txt
echo "" >> CUT_${1}.txt

for PART in `tail -n +4 ${FILENAME} | awk '{print $1}'`
do
    line=`tail -n +4 ${FILENAME} | grep $PART`
echo "${line}" >> CUT_${1}.txt
    total=`echo "${line}" | awk '{print $'"${totalawk}"'}'`
#echo "TOTAL : $total"
    cutminus1=""
    NbCuts=`echo "${line}" | wc -w`
    let "csa07idawk=totalawk+1"
    let "zjetvetoawk=totalawk+1"
    csa07id=""
		zjetveto=""
    effrel=""
    effabs=""
    percentagerel=""
    percentageabs=""
    csa07id=`echo "${line}" | awk '{print $'"${csa07idawk}"'}'`
    zjetveto=`echo "${line}" | awk '{print $'"${zjetvetoawk}"'}'`
#echo "CSA07ID : ${csa07id}"
    let "cut1=csa07idawk+1"
    let "cut1=zjetvetoawk+1"

    if [ "${PART}" = "SIGNAL" ]
    then
	lastcut="$NbCuts"
    else
	let "lastcut=NbCuts-1"
    fi

    if [ "${csa07id}" = "0" ]
    then
	cutminus1="${total}"
    else
	cutminus1="${csa07id}"
    fi

    if [ "${zjetveto}" = "0" ]
    then
			if [ "${csa07id}" = "0" ]
	    then
			  cutminus1="${total}"
	    else
			  cutminus1="${csa07id}"
	    fi
    else
			cutminus1="${zjetveto}"
    fi

    for j in `seq ${cut1} ${lastcut}`
    do
	cutvalue=`echo "${line}" | awk '{print $'"${j}"'}'`
#echo "$cutvalue"

	if [ ${cutminus1} != "0" ]
	then
	    effrel=`echo "scale=3; ${cutvalue}*100.0/${cutminus1}" | bc -ql`
	else
	    if [ ${cutminus2} != "0" ]
	    then
		effrel=`echo "scale=3; ${cutvalue}*100.0/${cutminus2}" | bc -ql`
	    else
		effrel="0"
	    fi
	fi
	percentagerel="${percentagerel}\t${effrel}"
	effabs=`echo "scale=3; ${cutvalue}*100.0/${total}" | bc -ql`
	percentageabs="${percentageabs}\t${effabs}"
	cutminus2="${cutminus1}"
	cutminus1="${cutvalue}"
    done
echo -e "rel (%):\t\t$percentagerel" >> CUT_${1}.txt
echo -e "abs (%):\t\t$percentageabs" >> CUT_${1}.txt
echo "" >> CUT_${1}.txt
    
done

echo ""
echo "Results written in CUT_${1}.txt"


exit
