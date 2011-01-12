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
TTJets_TuneZ2_7TeV_madgraph_tauola="121.0"
DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia="1614.0"
WJetsToLNu_TuneZ2_7TeV_madgraph_tauola="24640.0"
G4Jets_Pt_60to120_TuneZ2_7TeV_alpgen="32.08"
G4Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="0.25"
G4Jets_Pt_240to300_TuneZ2_7TeV_alpgen="0.42"
G4Jets_Pt_20to60_TuneZ2_7TeV_alpgen="148.30"
G4Jets_Pt_180to240_TuneZ2_7TeV_alpgen="1.40"
G4Jets_Pt_120to180_TuneZ2_7TeV_alpgen="5.73"
G3Jets_Pt_60to120_TuneZ2_7TeV_alpgen="118.70"
G3Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="0.47"
G3Jets_Pt_240to300_TuneZ2_7TeV_alpgen="0.76"
G3Jets_Pt_20to60_TuneZ2_7TeV_alpgen="794.70"
G3Jets_Pt_180to240_TuneZ2_7TeV_alpgen="3.09"
G3Jets_Pt_120to180_TuneZ2_7TeV_alpgen="15.27"
G2Jets_Pt_60to120_TuneZ2_7TeV_alpgen="425.80"
G2Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="0.72"
G2Jets_Pt_240to300_TuneZ2_7TeV_alpgen="1.45"
G2Jets_Pt_20to60_TuneZ2_7TeV_alpgen="4080.00"
G2Jets_Pt_180to240_TuneZ2_7TeV_alpgen="5.94"
G2Jets_Pt_120to180_TuneZ2_7TeV_alpgen="35.56"
QCD_Pt_20_MuEnrichedPt_15_TuneZ2_7TeV_pythia6="84679.3"

InitialNumberG_Pt_0to15_TuneZ2_7TeV_pythia6="1057100"
InitialNumberG_Pt_15to30_TuneZ2_7TeV_pythia6="1025840"
InitialNumberTTJets_TuneZ2_7TeV_madgraph_tauola="1164732"
InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia="1998931"
InitialNumberWJetsToLNu_TuneZ2_7TeV_madgraph_tauola="15123740"
InitialNumberG4Jets_Pt_60to120_TuneZ2_7TeV_alpgen="333214"
InitialNumberG4Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="336836"
InitialNumberG4Jets_Pt_240to300_TuneZ2_7TeV_alpgen="333241"
InitialNumberG4Jets_Pt_20to60_TuneZ2_7TeV_alpgen="335546"
InitialNumberG4Jets_Pt_180to240_TuneZ2_7TeV_alpgen="331020"
InitialNumberG4Jets_Pt_120to180_TuneZ2_7TeV_alpgen="328253"
InitialNumberG3Jets_Pt_60to120_TuneZ2_7TeV_alpgen="333681"
InitialNumberG3Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="311653"
InitialNumberG3Jets_Pt_240to300_TuneZ2_7TeV_alpgen="339273"
InitialNumberG3Jets_Pt_20to60_TuneZ2_7TeV_alpgen="322557"
InitialNumberG3Jets_Pt_180to240_TuneZ2_7TeV_alpgen="324607"
InitialNumberG3Jets_Pt_120to180_TuneZ2_7TeV_alpgen="331691"
InitialNumberG2Jets_Pt_60to120_TuneZ2_7TeV_alpgen="338909"
InitialNumberG2Jets_Pt_300to5000_TuneZ2_7TeV_alpgen="333630"
InitialNumberG2Jets_Pt_240to300_TuneZ2_7TeV_alpgen="331339"
InitialNumberG2Jets_Pt_20to60_TuneZ2_7TeV_alpgen="1782042"
InitialNumberG2Jets_Pt_180to240_TuneZ2_7TeV_alpgen="329962"
InitialNumberG2Jets_Pt_120to180_TuneZ2_7TeV_alpgen="330992"
InitialNumberQCD_Pt_20_MuEnrichedPt_15_TuneZ2_7TeV_pythia6="28779866"


cols=`head -n 4 RawSelectionCutsNumbers_${SelectionVersion}.txt | tail -n 1 | wc -w`
for sample in `tac RawSelectionCutsNumbers_${SelectionVersion}.txt | awk '{print $1}' | head -n -3`
do
#	echo ${sample}
	line=`grep -w "${sample}" RawSelectionCutsNumbers_${SelectionVersion}.txt`
#	echo ${line}
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
    elif [[ ${sample} = "TTJets_TuneZ2_7TeV-madgraph-tauola" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${TTJets_TuneZ2_7TeV_madgraph_tauola}"' / '"${InitialNumberTTJets_TuneZ2_7TeV_madgraph_tauola}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' / '"${InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "nonFSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' / '"${InitialNumberDYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "WJetsToLNu_TuneZ2_7TeV-madgraph-tauola" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${WJetsToLNu_TuneZ2_7TeV_madgraph_tauola}"' / '"${InitialNumberWJetsToLNu_TuneZ2_7TeV_madgraph_tauola}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-60to120_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-300to5000_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-240to300_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-20to60_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-180to240_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G4Jets_Pt-120to180_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G4Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG4Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-60to120_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-300to5000_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-240to300_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-20to60_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-180to240_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G3Jets_Pt-120to180_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G3Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG3Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-60to120_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_60to120_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-300to5000_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_300to5000_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-240to300_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_240to300_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-20to60_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_20to60_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-180to240_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_180to240_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "G2Jets_Pt-120to180_TuneZ2_7TeV-alpgen" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${G2Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' / '"${InitialNumberG2Jets_Pt_120to180_TuneZ2_7TeV_alpgen}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
#    elif [[ ${sample} = "SAMPLE" ]]
#    then
#      cut=`echo ${line} | awk '{printf "%4.5f", ('"${SAMPLE}"' / '"${InitialNumberSAMPLE}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt_20_MuEnrichedPt_15_TuneZ2_7TeV_pythia6}"' / '"${InitialNumberQCD_Pt_20_MuEnrichedPt_15_TuneZ2_7TeV_pythia6}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
		else
			cut=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
		fi
		allcuts="${allcuts}\t${cut}"
	done
	newline="${sample}\t${allcuts}"
	echo -e ${newline}  >> SelectionCutsNumbers_${SelectionVersion}.txt
done
exit 0


