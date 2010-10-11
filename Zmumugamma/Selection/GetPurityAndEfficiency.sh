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

IntegratedLuminosity="2859492.190e-06"

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
TTbarJets_Tauola="95.0"
WJets_7TeV="25090.0"
ZJets_7TeV="2224.0"
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

InitialNumberQCD_Pt15="6116800"
InitialNumberQCD_Pt30="5093840"
InitialNumberQCD_Pt80="3229000"
InitialNumberQCD_Pt170="3122500"
InitialNumberQCD_Pt300="3269645"
InitialNumberQCD_Pt470="2083653"
InitialNumberPhotonJet_Pt15="1221770"
InitialNumberPhotonJet_Pt30="1025300"
InitialNumberPhotonJet_Pt80="1287711"
InitialNumberPhotonJet_Pt170="1209600"
InitialNumberPhotonJet_Pt300="1033240"
InitialNumberTTbarJets_Tauola="1463572"
InitialNumberWJets_7TeV="10218854"
InitialNumberZJets_7TeV="1047008"
InitialNumberQCD_Mu_Pt20to30="10985188"
InitialNumberQCD_Mu_Pt30to50="6931182"
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
    elif [[ ${sample} = "QCD_Pt30" ]]
    then
 			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
     cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt30}"' / '"${InitialNumberQCD_Pt30}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt80" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt80}"' / '"${InitialNumberQCD_Pt80}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt170" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt170}"' / '"${InitialNumberQCD_Pt170}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt300" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt300}"' / '"${InitialNumberQCD_Pt300}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Pt470" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Pt470}"' / '"${InitialNumberQCD_Pt470}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt15" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${PhotonJet_Pt15}"' / '"${InitialNumberPhotonJet_Pt15}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt30" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${PhotonJet_Pt30}"' / '"${InitialNumberPhotonJet_Pt30}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt80" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${PhotonJet_Pt80}"' / '"${InitialNumberPhotonJet_Pt80}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt170" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${PhotonJet_Pt170}"' / '"${InitialNumberPhotonJet_Pt170}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "PhotonJet_Pt300" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${PhotonJet_Pt300}"' / '"${InitialNumberPhotonJet_Pt300}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "TTbarJets_Tauola-madgraph" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${TTbarJets_Tauola}"' / '"${InitialNumberTTbarJets_Tauola}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "WJets_7TeV-madgraph-tauola" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${WJets_7TeV}"' / '"${InitialNumberWJets_7TeV}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ZJets_7TeV-madgraph-tauola" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZJets_7TeV}"' / '"${InitialNumberZJets_7TeV}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt20to30" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt20to30}"' / '"${InitialNumberQCD_Mu_Pt20to30}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt30to50" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt30to50}"' / '"${InitialNumberQCD_Mu_Pt30to50}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt50to80" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt50to80}"' / '"${InitialNumberQCD_Mu_Pt50to80}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt80to120" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt80to120}"' / '"${InitialNumberQCD_Mu_Pt80to120}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt120to170" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt120to170}"' / '"${InitialNumberQCD_Mu_Pt120to170}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "QCD_Mu_Pt170toInf" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${QCD_Mu_Pt170toInf}"' / '"${InitialNumberQCD_Mu_Pt170toInf}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "InclusiveMu15" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${InclusiveMu15}"' / '"${InitialNumberInclusiveMu15}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt0to15" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt0to15}"' / '"${InitialNumberZmumuJet_Pt0to15}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt15to20" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt15to20}"' / '"${InitialNumberZmumuJet_Pt15to20}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt20to30" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt20to30}"' / '"${InitialNumberZmumuJet_Pt20to30}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt30to50" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt30to50}"' / '"${InitialNumberZmumuJet_Pt30to50}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt50to80" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt50to80}"' / '"${InitialNumberZmumuJet_Pt50to80}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt80to120" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt80to120}"' / '"${InitialNumberZmumuJet_Pt80to120}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt120to170" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt120to170}"' / '"${InitialNumberZmumuJet_Pt120to170}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt170to230" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt170to230}"' / '"${InitialNumberZmumuJet_Pt170to230}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt230to300" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt230to300}"' / '"${InitialNumberZmumuJet_Pt230to300}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "FSR_ZmumuJet_Pt300toInf" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt300toInf}"' / '"${InitialNumberZmumuJet_Pt300toInf}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt0to15" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt0to15}"' / '"${InitialNumberZmumuJet_Pt0to15}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt15to20" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt15to20}"' / '"${InitialNumberZmumuJet_Pt15to20}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt20to30" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt20to30}"' / '"${InitialNumberZmumuJet_Pt20to30}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt30to50" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt30to50}"' / '"${InitialNumberZmumuJet_Pt30to50}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt50to80" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt50to80}"' / '"${InitialNumberZmumuJet_Pt50to80}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt80to120" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt80to120}"' / '"${InitialNumberZmumuJet_Pt80to120}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt120to170" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt120to170}"' / '"${InitialNumberZmumuJet_Pt120to170}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt170to230" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt170to230}"' / '"${InitialNumberZmumuJet_Pt170to230}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt230to300" ]]
    then
			currentNumber=`echo ${line} | awk '{print $'"${currentColumn}"'}'`
			if [[ "${currentNumber}" == "0" ]]
			then
				currentNumber="1"
				iszero="1"
			fi
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt230to300}"' / '"${InitialNumberZmumuJet_Pt230to300}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
    elif [[ ${sample} = "ISR_ZmumuJet_Pt300toInf" ]]
    then
      cut=`echo ${line} | awk '{printf "%4.10f", ('"${ZmumuJet_Pt300toInf}"' / '"${InitialNumberZmumuJet_Pt300toInf}"' * '"${currentNumber}"' * '"${IntegratedLuminosity}"')}'`
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
for sample in `echo "QCD_Pt PhotonJet WJets QCD_Mu InclusiveMu15 TTbarJets ZJets FSR_ZmumuJet ISR_ZmumuJet"`
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
