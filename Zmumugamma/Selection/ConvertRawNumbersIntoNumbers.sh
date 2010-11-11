#!/usr/local/bin/bash
# Script to apply cross sections on  Numbers
# Written by O. Bondu (August 2010)

CMSSW_release="CMSSW_3_8_5_patch3"

syntax="${0} {SelectionVersion}"

if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi
SelectionVersion=${1}

echo "*** SelectionCutsNumbers_${SelectionVersion}.txt ***"

rm SelectionCutsNumbers_${SelectionVersion}.txt
echo -e "*** RESULTS ***" > SelectionCutsNumbers_${SelectionVersion}.txt
echo -e "Sample \t0\tPthatFilter\tCSA07ID\tZJETVETO\t1.a\t1.b\t1.c\t1.d\t1.e\t2.a\t2.b\t2.c\t3\t4\t5\t6\t7\t8\t9\t10\tSelected" >> SelectionCutsNumbers_${SelectionVersion}.txt
echo "" >> SelectionCutsNumbers_${SelectionVersion}.txt

IntegratedLuminosity="1"

QCD_Pt15="8.762e+08"
InitialNumberQCD_Pt15="6116800"

cols=`head -n 4 RawSelectionCutsNumbers_${SelectionVersion}.txt | tail -n 1 | wc -w`
for sample in `tac RawSelectionCutsNumbers_${SelectionVersion}.txt | awk '{print $1}' | head -n -3`
#for sample in QCD_Pt15
do
	line=`grep -w "${sample}" RawSelectionCutsNumbers_${SelectionVersion}.txt`
	newline=""
	cut=""
	allcuts=""
	for currentColumn in `seq 2 $cols`
	do
		if [[ ${sample} = "QCD_Pt15" ]]
		then
			cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt15}"' / '"${InitialNumberQCD_Pt15}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
#    elif [[ ${sample} = "SAMPLE" ]]
#    then
#      cut=`echo ${line} | awk '{printf "%4.5f", ('"${SAMPLE}"' / '"${InitialNumberSAMPLE}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
		else
			cut=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
		fi
		allcuts="${allcuts}\t${cut}"
	done
	newline="${sample}\t${allcuts}"
	echo -e ${newline}  >> SelectionCutsNumbers_${SelectionVersion}.txt
done
exit 0


