#!/bin/bash
# gets the selection efficiency and purity out of the weighted raw numbers. TODO: merge with Sum
# Written by O. Bondu (October 2010)

syntax="${0} {selection version}"
if [[ -z ${1} ]]
then
	echo "ERROR: syntax is ${syntax}"
	exit 2
fi

SelectionVersion=${1}
SELECTEDDIR=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/Selection/Selected/${SelectionVersion}
echo -e "*** PurityEfficiency_${SelectionVersion}.txt ***"
rm  PurityEfficiency_${SelectionVersion}.txt

IntegratedLuminosity="1"

QCD_Pt15="8.762e+08"
InitialNumberQCD_Pt15="6116800"

# ************
# First: if there is exactly zero RAW event, overestimate the RAW number of event to 1, to get an overestimate of the purity
# ************

cols=`head -n 4 RawSelectionCutsNumbers_${SelectionVersion}.txt | tail -n 1 | wc -w`
for sample in `tac RawSelectionCutsNumbers_${SelectionVersion}.txt | awk '{print $1}' | head -n -3 | grep -v part`
#for sample in QCD_Pt15
#for sample in ISR_ZmumuJet_Pt230to300
do
  line=`grep -w "${sample}" RawSelectionCutsNumbers_${SelectionVersion}.txt`
  newline=""
  cut=""
  allcuts=""
	iszero="0"
#  for currentColumn in `seq 2 $cols`
	for currentColumn in "${cols}"
  do
    if [[ ${sample} = "QCD_Pt15" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt15}"' / '"${InitialNumberQCD_Pt15}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
#    elif [[ ${sample} = "SAMPLE" ]]
#    then
#			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
#			if [[ "${currentNumber}" == "0" ]]
#			then
#				currentNumber="1"
#				iszero="1"
#			fi
#      cut=`echo ${line} | awk '{printf "%4.10f", ('"${SAMPLE}"' / '"${InitialNumberSAMPLE}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    else
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{print '"${currentNumber}"'}'`
    fi
    allcuts="${allcuts}\t${cut}"
  done
	if [[ "${iszero}" == "1" ]]
	then
		newline="FLAGGED_${sample}\t${allcuts}"
	else
	  newline="${sample}\t${allcuts}"
	fi
echo -e ${newline} >> PurityEfficiency_${SelectionVersion}_TEMP.txt

done

# ************
# Sum samples
# ************
for sample in `echo "QCD_Pt"`
do
	allcuts=""
	cols=`cat PurityEfficiency_${SelectionVersion}_TEMP.txt | grep ${sample} | head -n +1 | wc -w`
	for column in ${cols}
	do
		currentSum=`cat PurityEfficiency_${SelectionVersion}_TEMP.txt | grep ${sample} | awk 'BEGIN {SUM=0} {SUM+=$'"${column}"'} END {printf "%4.10f", SUM}'`
		cat PurityEfficiency_${SelectionVersion}_TEMP.txt | grep ${sample} | grep "FLAGGED" > /dev/null
		if [[ "$?" == "0" ]]
		then
			allcuts=`echo "${allcuts}\t MORE_THAN ${currentSum}"`
		else
			allcuts=`echo "${allcuts}\t${currentSum}"`
		fi
	done
echo -e "${sample}\t${allcuts}" >> PurityEfficiency_${SelectionVersion}_TEMP2.txt
echo -e "${sample}\t${allcuts}"
done

# ************
# COMPUTE PURITY
# ************
signal="FSR_ZmumuJet"
isExact="1"
allBGs="0.0"
BGList="PhotonJet WJets InclusiveMu15 TTbarJets ISR_ZmumuJet"
#for background in `echo "PhotonJet WJets QCD_Mu TTbarJets ISR_ZmumuJet"`
for background in `echo "${BGList}"`
do
	if [[ ${isExact} == "1" ]]
	then
		cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep "MORE_THAN" | grep ${background} > /dev/null
		if [[ $? == "0" ]]
		then
			isExact="0"
		fi
	fi
	cols=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${background} | wc -w`
	currentBG=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${background} | awk '{print $'"${cols}"'}'`
	allBGs=`echo "${allBGs} + ${currentBG}"`
done
cols=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${signal} | wc -w`
signalYield=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${signal} | awk '{print $'"${cols}"'}'`
PURITY=`awk 'BEGIN { printf "%4.10f", ('"${signalYield}"') / ('"${signalYield}"' + '"${allBGs}"')}'`

echo "Using ${BGList}: PURITY = ${PURITY}"
if [[ "${isExact}" == "0" ]]
then
	echo "PURITY < ${PURITY}" > PurityEfficiency_${SelectionVersion}.txt
else
	echo "PURITY = ${PURITY}" > PurityEfficiency_${SelectionVersion}.txt
fi


BGList="PhotonJet WJets QCD_Mu TTbarJets ISR_ZmumuJet"
for background in `echo "${BGList}"`
do
	if [[ ${isExact} == "1" ]]
	then
		cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep "MORE_THAN" | grep ${background} > /dev/null
		if [[ $? == "0" ]]
		then
			isExact="0"
		fi
	fi
	cols=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${background} | wc -w`
	currentBG=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${background} | awk '{print $'"${cols}"'}'`
	allBGs=`echo "${allBGs} + ${currentBG}"`
done
cols=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${signal} | wc -w`
signalYield=`cat PurityEfficiency_${SelectionVersion}_TEMP2.txt | grep ${signal} | awk '{print $'"${cols}"'}'`
PURITY=`awk 'BEGIN { printf "%4.10f", ('"${signalYield}"') / ('"${signalYield}"' + '"${allBGs}"')}'`

echo "Using ${BGList}: PURITY = ${PURITY}"
if [[ "${isExact}" == "0" ]]
then
	echo "PURITY < ${PURITY}" > PurityEfficiency_${SelectionVersion}.txt
else
	echo "PURITY = ${PURITY}" > PurityEfficiency_${SelectionVersion}.txt
fi

rm PurityEfficiency_${SelectionVersion}_TEMP.txt
rm PurityEfficiency_${SelectionVersion}_TEMP2.txt

# ************
# COMPUTE SIGNAL EFFICIENCY
# ************
line=`cat SelectionCutsNumbersSummed_${SelectionVersion}.txt | grep ${signal}`
cols=`echo ${line} | wc -w`
EFFICIENCY=`echo ${line} | awk '{printf "%4.10f", ( $'"${cols}"' / $5 )}'`
echo "EFFICIENCY = ${EFFICIENCY}" >> PurityEfficiency_${SelectionVersion}.txt
echo "EFFICIENCY = ${EFFICIENCY}"

exit 0
