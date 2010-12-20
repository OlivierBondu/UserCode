#!/usr/local/bin/bash
# Script to apply cross sections on  Numbers
# Written by O. Bondu (August 2010)

CMSSW_release="CMSSW_3_8_6_v6"

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

IntegratedLuminosity="36.145000992"

G_Pt_0to15_TuneZ2_7TeV_pythia6="84200000.0"
G_Pt_15to30_TuneZ2_7TeV_pythia6="171700.0"
TTJets_TuneZ2_7TeV_madgraph_tauola_v2="121.0"
DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia="1614.0"
WJetsToLNu_TuneZ2_7TeV_madgraph_tauola="24640.0"

InitialNumberG_Pt_0to15_TuneZ2_7TeV_pythia6="1057100"
InitialNumberG_Pt_15to30_TuneZ2_7TeV_pythia6="1025840"
InitialNumberTTJets_TuneZ2_7TeV_madgraph_tauola_v2="1164732"
InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia="1998931"
InitialNumberWJetsToLNu_TuneZ2_7TeV_madgraph_tauola="15123740"

cols=`head -n 4 RawSelectionCutsNumbers_${SelectionVersion}.txt | tail -n 1 | wc -w`
for sample in `tac RawSelectionCutsNumbers_${SelectionVersion}.txt | awk '{print $1}' | head -n -3`
do
	line=`grep -w "${sample}" RawSelectionCutsNumbers_${SelectionVersion}.txt`
	newline=""
	cut=""
	allcuts=""
	for currentColumn in `seq 2 $cols`
	do
    if [[ ${sample} = "G_Pt_0to15_TuneZ2_7TeV_pythia6" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G_Pt_0to15_TuneZ2_7TeV_pythia6}"' / '"${InitialNumberG_Pt_0to15_TuneZ2_7TeV_pythia6}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G_Pt_15to30_TuneZ2_7TeV_pythia6" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G_Pt_15to30_TuneZ2_7TeV_pythia6}"' / '"${InitialNumberG_Pt_15to30_TuneZ2_7TeV_pythia6}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "TTJets_TuneZ2_7TeV-madgraph-tauola_v2" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${TTJets_TuneZ2_7TeV_madgraph_tauola_v2}"' / '"${InitialNumberTTJets_TuneZ2_7TeV_madgraph_tauola_v2}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' / '"${InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' / '"${InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_v3" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${WJetsToLNu_TuneZ2_7TeV_madgraph_tauola}"' / '"${InitialNumberWJetsToLNu_TuneZ2_7TeV_madgraph_tauola}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
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


