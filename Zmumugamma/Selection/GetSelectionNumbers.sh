#!/usr/local/bin/bash
# Script to compute percentages and create LaTeX tables
# Rewritten by O.Bondu for CMSSW 361p4 (August 2010)

CMSSW_release="CMSSW_3_6_1_patch4"

syntax="${0} {SelectionVersion}"

if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi

SelectionVersion=${1}
SELECTEDDIR=/sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/Selection/Selected/${SelectionVersion}
LaTeXdir="LaTeXTables"

echo -e "*** SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt ***\n"
rm  SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt

if [ ! -d ${LaTeXdir} ]
then
  mkdir ${LaTeXdir}
fi

echo -e "Sample \t0\tPthatFilter\tCSA07ID\tZJETVETO\t1.a\t1.b\t1.c\t1.d\t1.e\t2.a\t2.b\t2.c\t3\t4\t5\t6\t7\t8\t9\t10" > SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt


for sample in `cat SelectionCutsNumbersSummed_${SelectionVersion}.txt | tail -n +4 | awk '{print $1}'`
do
	currentColumn="2"
	currentNumber=""
	relEff="rel eff\t"
	absEff="abs eff\t"
	line=`cat SelectionCutsNumbersSummed_${SelectionVersion}.txt | grep -w ${sample}`
	cols=`echo ${line} | wc -w`
	echo ${line} >> SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt
	relEff=`echo "${relEff}\t-"`
	absEff=`echo "${absEff}\t-"`
	rel=""
	abs=""
	initial=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
	for noCutColumn in `echo "PthatFilter CSA07ID ZJETVETO"`
	do
		currentColumn=$[${currentColumn}+1]
		currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
		if [[ ${currentNumber} != "0.00000" && ${currentNumber} != "0" ]]
		then
			initial=${currentNumber}
		fi
		relEff=`echo "${relEff}\t-"`
		absEff=`echo "${absEff}\t-"`
	done
	currentColumn=$[${currentColumn}+1]

# loop for relative efficiency
	previous=${initial}
	for col in `seq ${currentColumn} ${cols}`
  do
		if [[ ${previous} != "0.00000" && ${previous} != "0" ]]
		then
			currentEff=`echo ${line} | awk '{printf "%4.2E", ($'"${col}"' / '"${previous}"')}'`
			if [[ ${currentEff} == "1.00E+00" ]]
			then
				currentEff="1."
			fi
				relEff=`echo "${relEff}\t${currentEff}"`
			previous=`echo ${line} | awk '{print $'"${col}"'}'`
		else
			relEff=`echo "${relEff}\t-"`
		fi
	done
	echo -e ${relEff} >> SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt


# loop for absolute efficiency
	for col in `seq ${currentColumn} ${cols}`
	do
		currentEff=`echo ${line} | awk '{printf "%4.2E", ($'"${col}"' / '"${initial}"')}'`
		if [[ ${currentEff} != "0.00E+00" ]]
		then
			absEff=`echo "${absEff}\t${currentEff}"`
		else
			absEff=`echo "${absEff}\t-"`
		fi
	done
	echo -e ${absEff} >> SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt

done

echo -e "\nTranspose"
cp SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tmp
sed -i -e 's,_,,g' ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tmp
sed -i -e 's,rel eff,$\\epsilon_{rel}$,g' -e 's,abs eff,$\\epsilon_{abs}$,g' ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tmp

./transpose.sh ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tmp > ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt
rm ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tmp

echo -e "\nPut LaTeX format"
echo "
\documentclass[landscape, 6pt, a4paper]{article}

\topmargin = -1cm
\textheight= 23.5cm
\textwidth = 16cm
\oddsidemargin = 0cm

\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{graphicx}
%\usepackage{hepunits}
\usepackage[english]{babel}
\usepackage[colorlinks]{hyperref}
\usepackage{color}

\begin{document}
" > ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tex

columns=`head -n 1 ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt | wc -w`
ccc=""
for col in `seq 1 ${columns}`
do
	ccc=`echo "${ccc}c"`
done

echo "
\begin{tabular}{${ccc}}
" >> ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tex


cat ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.txt | sed 's/^0/\\hline\n0/1' | sed 's/^/\\\\/g' |sed 's/ / \& /g' >> ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tex
echo "\end{tabular}
\end{document}" >> ${LaTeXdir}/SelectionCutsNumbersEfficiencies_${SelectionVersion}.tex





exit 0



































NB=`'ls' ${SELECTEDDIR} | wc -l`
echo "Processing .out files"
for sample in `'ls' ${SELECTEDDIR}`
do
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
		echo -e  "${SAMPLEandNb}\t( ${NbOfFiles} )${allcuts}" >> TEMPRESULTS_${SelectionVersion}.txt
		NbOfFiles=""
		total=""
		csa07id=""
		allcuts=""
		cutvalue=""																								
		done # end of loop over sample files
done # end of loop over samples

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

cat TEMPRESULTS_${SelectionVersion}.txt | sort >> ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.txt

rm TEMPRESULTS_${SelectionVersion}.txt

echo -e "\nTranspose"

./transpose.sh ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.txt > ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.tmp

echo -e "\nPut LaTeX format"
echo "
\documentclass[10pt, a4paper]{article}

\topmargin = -1cm
\textheight= 23.5cm
\textwidth = 16cm
\oddsidemargin = 0cm

\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{graphicx}
%\usepackage{hepunits}
\usepackage[english]{babel}
\usepackage[colorlinks]{hyperref}
\usepackage{color}

\begin{document}
\begin{tabular}{ccc}
" > ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.tex
cat ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.tmp | sed 's/^0/\\hline\n0/1' | sed 's/^/\\\\/g' |sed 's/ / \& /g' >> ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.tex
echo "\end{tabular}
\end{document}" >> ${currentDay}/RawSelectionCutsNumbers_${SelectionVersion}.tex

exit 0


