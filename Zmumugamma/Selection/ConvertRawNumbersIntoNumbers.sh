#!/usr/local/bin/bash
# Script to apply cross sections on  Numbers
# Written by O. Bondu (August 2010)

CMSSW_release="CMSSW_3_6_1_patch4"

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

IntegratedLuminosity="301.213e-03"

QCD_Pt15="8.762e+08"
QCD_Pt30="6.041e+07" 
QCD_Pt80="9.238e+05" 
QCD_Pt170="2.547e+04" 
QCD_Pt300="1.256e+03" 
QCD_Pt470="8.798e+01" 
PhotonJet_Pt15="1.922e+05" 
PhotonJet_Pt30="2.007e+04" 
PhotonJet_Pt80="5.565e+02" 
PhotonJet_Pt170="2.437e+01"
PhotonJet_Pt300="1.636e+00"
TTbarJets_Tauola="33.25"
WJets_7TeV="11541.4"
ZJets_7TeV="911.84"
QCD_Mu_Pt20to30="1208700.0"
QCD_Mu_Pt30to50="654360.0"
QCD_Mu_Pt50to80="138846.0"
QCD_Mu_Pt80to120="29045.0"
QCD_Mu_Pt120to170="6095.0"
QCD_Mu_Pt170toInf="1612.8"
InclusiveMu15="79687.96"
ZmumuJet_Pt0to15="4.434e+03"
ZmumuJet_Pt15to20="1.454e+02"
ZmumuJet_Pt20to30="1.318e+02"
ZmumuJet_Pt30to50="8.438e+01"
ZmumuJet_Pt50to80="3.235e+01"
ZmumuJet_Pt80to120="9.981e+00"
ZmumuJet_Pt120to170="2.760e+00"
ZmumuJet_Pt170to230="7.241e-01"
ZmumuJet_Pt230to300="1.946e-01"
ZmumuJet_Pt300toInf="7.627e-02"

InitialNumberQCD_Pt15="6196800"
InitialNumberQCD_Pt30="5093840"
InitialNumberQCD_Pt80="3229000"
InitialNumberQCD_Pt170="3162500"
InitialNumberQCD_Pt300="3269645"
InitialNumberQCD_Pt470="2093653"
InitialNumberPhotonJet_Pt15="1221770"
InitialNumberPhotonJet_Pt30="1025300"
InitialNumberPhotonJet_Pt80="1287711"
InitialNumberPhotonJet_Pt170="1209600"
InitialNumberPhotonJet_Pt300="1033240"
InitialNumberTTbarJets_Tauola="1463572"
InitialNumberWJets_7TeV="10218854"
InitialNumberZJets_7TeV="1047008"
InitialNumberQCD_Mu_Pt20to30="11035188"
InitialNumberQCD_Mu_Pt30to50="6951182"
InitialNumberQCD_Mu_Pt50to80="2542308"
InitialNumberQCD_Mu_Pt80to120="523053"
InitialNumberQCD_Mu_Pt120to170="316630"
InitialNumberQCD_Mu_Pt170toInf="262036"
InitialNumberInclusiveMu15="5120334"
InitialNumberZmumuJet_Pt0to15="235420"
InitialNumberZmumuJet_Pt15to20="222730"
InitialNumberZmumuJet_Pt20to30="164190"
InitialNumberZmumuJet_Pt30to50="163920"
InitialNumberZmumuJet_Pt50to80="106016"
InitialNumberZmumuJet_Pt80to120="107759"
InitialNumberZmumuJet_Pt120to170="177408"
InitialNumberZmumuJet_Pt170to230="178400"
InitialNumberZmumuJet_Pt230to300="176485"
InitialNumberZmumuJet_Pt300toInf="109316"


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
		elif [[ ${sample} = "QCD_Pt30" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt30}"' / '"${InitialNumberQCD_Pt30}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt80" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt80}"' / '"${InitialNumberQCD_Pt80}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt170" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt170}"' / '"${InitialNumberQCD_Pt170}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt300" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt300}"' / '"${InitialNumberQCD_Pt300}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt470" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Pt470}"' / '"${InitialNumberQCD_Pt470}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
		elif [[ ${sample} = "PhotonJet_Pt15" ]]
		then
			cut=`echo ${line} | awk '{printf "%4.5f", ('"${PhotonJet_Pt15}"' / '"${InitialNumberPhotonJet_Pt15}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
		elif [[ ${sample} = "PhotonJet_Pt30" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${PhotonJet_Pt30}"' / '"${InitialNumberPhotonJet_Pt30}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt80" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${PhotonJet_Pt80}"' / '"${InitialNumberPhotonJet_Pt80}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt170" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${PhotonJet_Pt170}"' / '"${InitialNumberPhotonJet_Pt170}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt300" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${PhotonJet_Pt300}"' / '"${InitialNumberPhotonJet_Pt300}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "TTbarJets_Tauola-madgraph" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${TTbarJets_Tauola}"' / '"${InitialNumberTTbarJets_Tauola}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "WJets_7TeV-madgraph-tauola" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${WJets_7TeV}"' / '"${InitialNumberWJets_7TeV}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZJets_7TeV-madgraph-tauola" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZJets_7TeV}"' / '"${InitialNumberZJets_7TeV}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt20to30" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt20to30}"' / '"${InitialNumberQCD_Mu_Pt20to30}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt30to50" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt30to50}"' / '"${InitialNumberQCD_Mu_Pt30to50}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt50to80" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt50to80}"' / '"${InitialNumberQCD_Mu_Pt50to80}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt80to120" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt80to120}"' / '"${InitialNumberQCD_Mu_Pt80to120}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt120to170" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt120to170}"' / '"${InitialNumberQCD_Mu_Pt120to170}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt170toInf" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${QCD_Mu_Pt170toInf}"' / '"${InitialNumberQCD_Mu_Pt170toInf}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "InclusiveMu15" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${InclusiveMu15}"' / '"${InitialNumberInclusiveMu15}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt0to15" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt0to15}"' / '"${InitialNumberZmumuJet_Pt0to15}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt15to20" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt15to20}"' / '"${InitialNumberZmumuJet_Pt15to20}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt20to30" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt20to30}"' / '"${InitialNumberZmumuJet_Pt20to30}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt30to50" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt30to50}"' / '"${InitialNumberZmumuJet_Pt30to50}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt50to80" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt50to80}"' / '"${InitialNumberZmumuJet_Pt50to80}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt80to120" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt80to120}"' / '"${InitialNumberZmumuJet_Pt80to120}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt120to170" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt120to170}"' / '"${InitialNumberZmumuJet_Pt120to170}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt170to230" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt170to230}"' / '"${InitialNumberZmumuJet_Pt170to230}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt230to300" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt230to300}"' / '"${InitialNumberZmumuJet_Pt230to300}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZmumuJet_Pt300toInf" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.5f", ('"${ZmumuJet_Pt300toInf}"' / '"${InitialNumberZmumuJet_Pt300toInf}"' * $'"${currentColumn}"' * '"${IntegratedLuminosity}"')}'`
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


