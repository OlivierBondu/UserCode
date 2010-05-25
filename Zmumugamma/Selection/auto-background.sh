#!/usr/local/bin/bash
# helper script to launch several jobs by type
# Created by Clement Baty
# Modified by Olivier Bondu (November 2009)
# Adapted for CMSSW_336 (February 2010)

CMSSWRelease="CMSSW_3_5_7"
export LOCALDIR="/sps/cms/obondu/${CMSSWRelease}/src/Zmumugamma/Selection"


ST=0

## SIGNAL
signal=0		# 7TeV_Zmumugamma

## ZJETS
zjets_madgraph=0	# ZJETS MADGRAPH
z1j_alpgen=0		# Z+1J ALPGEN
z2j_alpgen=0		# Z+2J ALPGEN
z3j_alpgen=0		# Z+3J ALPGEN
z4j_alpgen=0		# Z+4J ALPGEN
z5j_alpgen=0		# Z+5J ALPGEN

## WJETS
w1j_alpgen=0		# W+1J ALPGEN
w2j_alpgen=0		# W+2J ALPGEN
w3j_alpgen=0		# W+3J ALPGEN
w4j_alpgen=0		# W+4J ALPGEN
w5j_alpgen=0		# W+5J ALPGEN

## bosonjets
z0j_alpgen=0		# Z+0J ALPGEN
w0j_alpgen=0		# W+0J ALPGEN

## InclusiveBMuPt15 / InclusivePPmuX / QCD_BCtoMu_Pt20
incmu=0			# InclusiveMu15
incppmux=0		# InclusivePPmuX
incqcd=0		# QCD_BCtoMu_Pt20

## TTbar 
ttbar_alpgen=0		# TTBAR + M JETS ALPGEN
ttbar_madgraph=0	# TTBAR + M JETS MADGRAPH

## GammaJets 
gamma_alpgen=0		# GAMMA + N JETS ALPGEN
gamma_madgraph=0	# GAMMA + N JETS MADGRAPH

mytest=0

# Select the part for after
if [[ -z $1 ]]
	then
		if [[ -z $2 ]]
		then
			echo "Syntax `basename $0` PART TYPE" && exit 1
		fi
		echo "Syntax `basename $0` PART TYPE" && exit 1
	else
	case "$1" in
		"all" ) signal=1 ; incmu=1 ; zjets_madgraph=0 ; z1j_alpgen=1 ; z2j_alpgen=0 ; z3j_alpgen=0 ; z4j_alpgen=0 ; z5j_alpgen=0 ; w1j_alpgen=1 ; w2j_alpgen=1 ; w3j_alpgen=1 ; w4j_alpgen=1 ; w5j_alpgen=1 ; w0j_alpgen=0 ; z0j_alpgen=0 ;  ttbar_alpgen=1 ; ttbar_madgraph=0 ; gamma_alpgen=1 ; gamma_madgraph=0 ; incppmux=0 ; incqcd=0 ;;
		"signal" ) signal=1 ;;
		"zjets" ) zjets_madgraph=1 ; z1j_alpgen=1 ; z2j_alpgen=1 ; z3j_alpgen=1 ; z4j_alpgen=1 ; z5j_alpgen=1 ;;
		"zjets-alpgen" ) z1j_alpgen=1 ; z2j_alpgen=0 ; z3j_alpgen=0 ; z4j_alpgen=0 ; z5j_alpgen=0 ;;
		"zjets-madgraph" ) zjets_madgraph=1 ;;
		"wjets" )  wj_alpgen=1 ; w2j_alpgen=1 ; w3j_alpgen=1 ; w4j_alpgen=1 ; w5j_alpgen=1 ;;
		"bosonj" ) w0j_alpgen=1 ; z0j_alpgen=1 ;;
		"incmu" ) incmu=1 ;;
		"ttbar" ) ttbar_alpgen=1 ; ttbar_madgraph=1 ;;
		"ttbar-alpgen" ) ttbar_alpgen=1 ;;
		"ttbar-madgraph" ) ttbar_madgraph=1 ;;
		"gjets" ) gamma_alpgen=1 ; gamma_madgraph=1 ;;
		"gamma-alpgen" ) gamma_alpgen=1 ;;
		"gamma-madgraph" ) gamma_madgraph=1 ;;
		"incppmux" ) incppmux=1 ;;
		"incqcd" ) incqcd=1 ;;
		"test" ) mytest=1 ;;
		"help" )
		echo "Choice is between the following : all, signal, zjets [zjets-alpgen, zjets-madgraph], wjets, bosonjets, incmu, ttbar [ttbar-alpgen, ttbar-madgraph], gjets [gamma-alpgen, gamma-madgraph], incppmux, incqcd or test" 
		exit 0 
		;;
		* ) echo "Syntax: `basename $0` PART TYPE || help" && exit 1;;
	esac
fi

echo "Your selection is to run the following selection signal=$signal, zjetsmg=$zjets_madgraph, incmu=$incmu, zjets-madgraph=$zjets_madgraph, zjets-alpgen=$z1j_alpgen, bosonjets=$w0j_alpgen, ttbar_alpgen=$ttbar_alpgen, ttbar_madgraph=$ttbar_madgraph, gamma-alpgen=$gamma_alpgen, gamma-madgraph=$gamma_madgraph, incppmux=$incppmux incqcd=$incqcd"
TYPE=$2

#### FOR SIGNAL ####
if [[ $signal -eq 1 ]] 
	then
	# STEP 0 == SIGNAL
	# CREATE JOBS
	for iPART in `seq 0 55`
	do
				export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Zmumugamma"
				sed -e s/MYPART/7TeV_Zmumugamma/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_7TeV_Zmumugamma_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_7TeV_Zmumugamma_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_7TeV_Zmumugamma_${iPART}.sh -N run_7TeV_Zmumugamma_${iPART}_${TYPE}
        sleep $ST
	done
fi

#### FOR Z + NJETS ####
if [[ $zjets_madgraph -eq 1 ]]
	then
	# STEP 1.A == ZJets-madgraph
	# CREATE JOBS
	for PART in `seq 1 13`
	do
  	export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_ZJets-madgraph"
		sed -e s/MYPART/7TeV_ZJets-madgraph/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_ZJets_madgraph_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_ZJets_madgraph_${PART}.sh
		./runjob ${EXPORTDIR}/run_ZJets_madgraph_${PART}.sh -N run_ZJets_madgraph_${PART}_${TYPE}
		sleep $ST 
	done
fi

if [[ $z1j_alpgen -eq 1 ]]
	then 
	# STEP 1.1 == Z + 1JETS ALPGEN

        # CREATE JOBS 0_100
  			export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z1Jets_Pt0to100-alpgen"
        sed -e s/MYPART/7TeV_Z1Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z1Jets_Pt0to100-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z1Jets_Pt0to100-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z1Jets_Pt0to100-alpgen_all.sh -N run_Z1Jets_Pt0to100-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 100_300
        for iPART in `seq 1 122`
				do
				export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z1Jets_Pt100to300-alpgen"
				sed -e s/MYPART/7TeV_Z1Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z1Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z1Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_Z1Jets_Pt100to300-alpgen_${iPART}.sh -N run_Z1Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
				done

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z1Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_Z1Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z1Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z1Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z1Jets_Pt300to800-alpgen_all.sh -N run_Z1Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z1Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_Z1Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z1Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z1Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z1Jets_Pt800to1600-alpgen_all.sh -N run_Z1Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z1Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_Z1Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z1Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z1Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z1Jets_Pt1600toInf-alpgen_all.sh -N run_Z1Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $z2j_alpgen -eq 1 ]]
	then 
	# STEP 1.2 == Z + 2JETS ALPGEN

	# CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z2Jets_Pt0to100-alpgen"
	sed -e s/MYPART/7TeV_Z2Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z2Jets_Pt0to100-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z2Jets_Pt0to100-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z2Jets_Pt0to100-alpgen_all.sh -N run_Z2Jets_Pt0to100-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 100_300
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z2Jets_Pt100to300-alpgen"
	sed -e s/MYPART/7TeV_Z2Jets_Pt100to300-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z2Jets_Pt100to300-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z2Jets_Pt100to300-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z2Jets_Pt100to300-alpgen_all.sh -N run_Z2Jets_Pt100to300-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z2Jets_Pt300to800-alpgen"
	sed -e s/MYPART/7TeV_Z2Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z2Jets_Pt300to800-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z2Jets_Pt300to800-alpgen_all.sh
       ./runjob ${EXPORTDIR}/run_Z2Jets_Pt300to800-alpgen_all.sh -N run_Z2Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

	# CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z2Jets_Pt800to1600-alpgen"
	sed -e s/MYPART/7TeV_Z2Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z2Jets_Pt800to1600-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z2Jets_Pt800to1600-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z2Jets_Pt800to1600-alpgen_all.sh -N run_Z2Jets_Pt800to1600-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z2Jets_Pt1600toInf-alpgen"
	sed -e s/MYPART/7TeV_Z2Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z2Jets_Pt1600toInf-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z2Jets_Pt1600toInf-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z2Jets_Pt1600toInf-alpgen_all.sh -N run_Z2Jets_Pt1600toInf-alpgen_all_${TYPE}
	sleep $ST
fi

if [[ $z3j_alpgen -eq 1 ]]
	then 
	# STEP 1.3 == Z + 3JETS ALPGEN

	# CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z3Jets_Pt0to100-alpgen"
	sed -e s/MYPART/7TeV_Z3Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z3Jets_Pt0to100-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z3Jets_Pt0to100-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z3Jets_Pt0to100-alpgen_all.sh -N run_Z3Jets_Pt0to100-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 100_300
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z3Jets_Pt100to300-alpgen"
	sed -e s/MYPART/7TeV_Z3Jets_Pt100to300-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z3Jets_Pt100to300-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z3Jets_Pt100to300-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z3Jets_Pt100to300-alpgen_all.sh -N run_Z3Jets_Pt100to300-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z3Jets_Pt300to800-alpgen"
	sed -e s/MYPART/7TeV_Z3Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z3Jets_Pt300to800-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z3Jets_Pt300to800-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z3Jets_Pt300to800-alpgen_all.sh -N run_Z3Jets_Pt300to800-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z3Jets_Pt800to1600-alpgen"
	sed -e s/MYPART/7TeV_Z3Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z3Jets_Pt800to1600-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z3Jets_Pt800to1600-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z3Jets_Pt800to1600-alpgen_all.sh -N run_Z3Jets_Pt800to1600-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z3Jets_Pt1600toInf-alpgen"
	sed -e s/MYPART/7TeV_Z3Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z3Jets_Pt1600toInf-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z3Jets_Pt1600toInf-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z3Jets_Pt1600toInf-alpgen_all.sh -N run_Z3Jets_Pt1600toInf-alpgen_all_${TYPE}
	sleep $ST
fi

if [[ $z4j_alpgen -eq 1 ]]
	then 
	# STEP 1.4 == Z + 4JETS ALPGEN

	# CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z4Jets_Pt0to100-alpgen"
	sed -e s/MYPART/7TeV_Z4Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z4Jets_Pt0to100-alpgen_all.sh
	# SUBMIT JOBS
	chmod u+x ${EXPORTDIR}/run_Z4Jets_Pt0to100-alpgen_all.sh
	./runjob ${EXPORTDIR}/run_Z4Jets_Pt0to100-alpgen_all.sh -N run_Z4Jets_Pt0to100-alpgen_all_${TYPE}
	sleep $ST

	# CREATE JOBS 100_300
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z4Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_Z4Jets_Pt100to300-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z4Jets_Pt100to300-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z4Jets_Pt100to300-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z4Jets_Pt100to300-alpgen_all.sh -N run_Z4Jets_Pt100to300-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z4Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_Z4Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z4Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z4Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z4Jets_Pt300to800-alpgen_all.sh -N run_Z4Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z4Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_Z4Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z4Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z4Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z4Jets_Pt800to1600-alpgen_all.sh -N run_Z4Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z4Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_Z4Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z4Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z4Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z4Jets_Pt1600toInf-alpgen_all.sh -N run_Z4Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $z5j_alpgen -eq 1 ]]
	then 
	# STEP 1.5 == Z + 5JETS ALPGEN

        # CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z5Jets_Pt0to100-alpgen"
        sed -e s/MYPART/7TeV_Z5Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z5Jets_Pt0to100-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z5Jets_Pt0to100-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z5Jets_Pt0to100-alpgen_all.sh -N run_Z5Jets_Pt0to100-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 100_300
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z5Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_Z5Jets_Pt100to300-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z5Jets_Pt100to300-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z5Jets_Pt100to300-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z5Jets_Pt100to300-alpgen_all.sh -N run_Z5Jets_Pt100to300-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z5Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_Z5Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z5Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z5Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z5Jets_Pt300to800-alpgen_all.sh -N run_Z5Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z5Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_Z5Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z5Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z5Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z5Jets_Pt800to1600-alpgen_all.sh -N run_Z5Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z5Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_Z5Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z5Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_Z5Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_Z5Jets_Pt1600toInf-alpgen_all.sh -N run_Z5Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

#### WNJETS ####
if [[ $w1j_alpgen -eq 1 ]]
        then
        # STEP 2.1 == W + 1JETS ALPGEN

        # CREATE JOBS 0_100
	# CREATE JOBS
	for PART in `seq 1 7`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W1Jets_Pt0to100-alpgen"
		sed -e s/MYPART/7TeV_W1Jets_Pt0to100-alpgen/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W1Jets_Pt0to100-alpgen_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_W1Jets_Pt0to100-alpgen_${PART}.sh
		./runjob ${EXPORTDIR}/run_W1Jets_Pt0to100-alpgen_${PART}.sh -N run_W1Jets_Pt0to100-alpgen_${PART}_${TYPE}
		sleep $ST 
	done

        # CREATE JOBS 100_300
        	for iPART in `seq 1 84`
	do
export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W1Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_W1Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W1Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W1Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_W1Jets_Pt100to300-alpgen_${iPART}.sh -N run_W1Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
done

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W1Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_W1Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W1Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W1Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W1Jets_Pt300to800-alpgen_all.sh -N run_W1Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W1Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_W1Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W1Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W1Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W1Jets_Pt800to1600-alpgen_all.sh -N run_W1Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W1Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_W1Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W1Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W1Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W1Jets_Pt1600toInf-alpgen_all.sh -N run_W1Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $w2j_alpgen -eq 1 ]]
        then
        # STEP 2.2 == W + 2jetS ALPGEN

        # CREATE JOBS 0_100
	for i in `seq 1 2`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W2Jets_Pt0to100-alpgen"
		sed -e s/MYPART/7TeV_W2Jets_Pt0to100-alpgen/g -e s/MYSUBPART/${i}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W2Jets_Pt0to100-alpgen_${i}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_W2Jets_Pt0to100-alpgen_${i}.sh
		./runjob ${EXPORTDIR}/run_W2Jets_Pt0to100-alpgen_${i}.sh -N run_W2Jets_Pt0to100-alpgen_${i}_${TYPE}
		sleep $ST
	done

        # CREATE JOBS 100_300
	for iPART in `seq 1 69`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W2Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_W2Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W2Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W2Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_W2Jets_Pt100to300-alpgen_${iPART}.sh -N run_W2Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
done

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W2Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_W2Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W2Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W2Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W2Jets_Pt300to800-alpgen_all.sh -N run_W2Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W2Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_W2Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W2Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W2Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W2Jets_Pt800to1600-alpgen_all.sh -N run_W2Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W2Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_W2Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W2Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W2Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W2Jets_Pt1600toInf-alpgen_all.sh -N run_W2Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $w3j_alpgen -eq 1 ]]
        then
        # STEP 2.2 == W + 3jetS ALPGEN

        # CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W3Jets_Pt0to100-alpgen"
        sed -e s/MYPART/7TeV_W3Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W3Jets_Pt0to100-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W3Jets_Pt0to100-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W3Jets_Pt0to100-alpgen_all.sh -N run_W3Jets_Pt0to100-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 100_300
	for iPART in `seq 1 32`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W3Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_W3Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W3Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W3Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_W3Jets_Pt100to300-alpgen_${iPART}.sh -N run_W3Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
done

        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W3Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_W3Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W3Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W3Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W3Jets_Pt300to800-alpgen_all.sh -N run_W3Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W3Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_W3Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W3Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W3Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W3Jets_Pt800to1600-alpgen_all.sh -N run_W3Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W3Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_W3Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W3Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W3Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W3Jets_Pt1600toInf-alpgen_all.sh -N run_W3Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $w4j_alpgen -eq 1 ]]
        then
        # STEP 2.2 == W + 4jetS ALPGEN

        # CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W4Jets_Pt0to100-alpgen"
        sed -e s/MYPART/7TeV_W4Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W4Jets_Pt0to100-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W4Jets_Pt0to100-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W4Jets_Pt0to100-alpgen_all.sh -N run_W4Jets_Pt0to100-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 100_300
 	for iPART in `seq 1 6`
	do
       export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W4Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_W4Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W4Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W4Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_W4Jets_Pt100to300-alpgen_${iPART}.sh -N run_W4Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
done
				
        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W4Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_W4Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W4Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W4Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W4Jets_Pt300to800-alpgen_all.sh -N run_W4Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W4Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_W4Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W4Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W4Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W4Jets_Pt800to1600-alpgen_all.sh -N run_W4Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W4Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_W4Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W4Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W4Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W4Jets_Pt1600toInf-alpgen_all.sh -N run_W4Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

if [[ $w5j_alpgen -eq 1 ]]
        then
        # STEP 2.2 == W + 5jetS ALPGEN

        # CREATE JOBS 0_100
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W5Jets_Pt0to100-alpgen"
        sed -e s/MYPART/7TeV_W5Jets_Pt0to100-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W5Jets_Pt0to100-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W5Jets_Pt0to100-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W5Jets_Pt0to100-alpgen_all.sh -N run_W5Jets_Pt0to100-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 100_300
   	for iPART in `seq 1 6`
	do
     export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W5Jets_Pt100to300-alpgen"
        sed -e s/MYPART/7TeV_W5Jets_Pt100to300-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W5Jets_Pt100to300-alpgen_${iPART}.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W5Jets_Pt100to300-alpgen_${iPART}.sh
        ./runjob ${EXPORTDIR}/run_W5Jets_Pt100to300-alpgen_${iPART}.sh -N run_W5Jets_Pt100to300-alpgen_${iPART}_${TYPE}
        sleep $ST
done
				
        # CREATE JOBS 300_800
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W5Jets_Pt300to800-alpgen"
        sed -e s/MYPART/7TeV_W5Jets_Pt300to800-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W5Jets_Pt300to800-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W5Jets_Pt300to800-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W5Jets_Pt300to800-alpgen_all.sh -N run_W5Jets_Pt300to800-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 800_1600
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W5Jets_Pt800to1600-alpgen"
        sed -e s/MYPART/7TeV_W5Jets_Pt800to1600-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W5Jets_Pt800to1600-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W5Jets_Pt800to1600-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W5Jets_Pt800to1600-alpgen_all.sh -N run_W5Jets_Pt800to1600-alpgen_all_${TYPE}
        sleep $ST

        # CREATE JOBS 1600_Inf
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W5Jets_Pt1600toInf-alpgen"
        sed -e s/MYPART/7TeV_W5Jets_Pt1600toInf-alpgen/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W5Jets_Pt1600toInf-alpgen_all.sh
        # SUBMIT JOBS
        chmod u+x ${EXPORTDIR}/run_W5Jets_Pt1600toInf-alpgen_all.sh
        ./runjob ${EXPORTDIR}/run_W5Jets_Pt1600toInf-alpgen_all.sh -N run_W5Jets_Pt1600toInf-alpgen_all_${TYPE}
        sleep $ST
fi

#### BOSONS with NO JETS ####

if [[ $z0j_alpgen -eq 1 ]]
	then
	# STEP 3.A == Z+0JETS
	# CREATE JOBS
	for PART in `seq 1 4`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_Z0Jets-alpgen"
		sed -e s/MYPART/7TeV_Z0Jets-alpgen/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_Z0Jets-alpgen_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_Z0Jets-alpgen_${PART}.sh
		./runjob ${EXPORTDIR}/run_Z0Jets-alpgen_${PART}.sh -N run_Z0Jets-alpgen_${PART}_${TYPE}
		sleep $ST 
	done
fi

if [[ $w0j_alpgen -eq 1 ]]
	then
	# STEP 3.B == W+0JETS
	# CREATE JOBS
	for PART in `seq 1 48`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_W0Jets-alpgen"
		sed -e s/MYPART/7TeV_W0Jets-alpgen/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_W0Jets-alpgen_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_W0Jets-alpgen_${PART}.sh
		./runjob ${EXPORTDIR}/run_W0Jets-alpgen_${PART}.sh -N run_W0Jets-alpgen_${PART}_${TYPE}
		sleep $ST 
	done
fi

#### INCLUSIVEBMU ####
if [[ $incmu -eq 1 ]]
	then
	# STEP 4.A == InclusiveBMuPt15
	# CREATE JOBS
	for PART in `seq 1 224`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_InclusiveMu15"
		sed -e s/MYPART/7TeV_InclusiveMu15/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_InclusiveMu15_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_InclusiveMu15_${PART}.sh
		./runjob ${EXPORTDIR}/run_InclusiveMu15_${PART}.sh -N run_InclusiveMu15_${PART}_${TYPE}
		sleep $ST 
	done
fi

#### TTBAR ####
if [[ $ttbar_madgraph -eq 1 ]]
	then
	# STEP 5.A == TTJets-madgraph
	# CREATE JOBS
	for PART in `seq 1 5`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTJets-madgraph"
		sed -e s/MYPART/7TeV_TTJets-madgraph/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTJets-madgraph_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_TTJets-madgraph_${PART}.sh
		./runjob ${EXPORTDIR}/run_TTJets-madgraph_${PART}.sh -N run_TTJets-madgraph_${PART}_${TYPE}
		sleep $ST 
	done
fi

if [[ $ttbar_alpgen -eq 1 ]]
	then
	# STEP 5.B.0 == TTbar_0j-alpgen
	# CREATE JOBS
	for PART in `seq 1 2`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTbar0Jets_40GeVthreshold-alpgen"
		sed -e s/MYPART/7TeV_TTbar0Jets_40GeVthreshold-alpgen/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTbar0Jets_40GeVthreshold-alpgen_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_TTbar0Jets_40GeVthreshold-alpgen_${PART}.sh
		./runjob ${EXPORTDIR}/run_TTbar0Jets_40GeVthreshold-alpgen_${PART}.sh -N run_TTbar0Jets_40GeVthreshold-alpgen_${PART}_${TYPE}
		sleep $ST 
	done

	# STEP 5.B.1 == TTbar_1j-alpgen
	# CREATE JOBS
	for iPART in `seq 1 209`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTbar1Jets_40GeVthreshold-alpgen"
	sed -e s/MYPART/7TeV_TTbar1Jets_40GeVthreshold-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTbar1Jets_40GeVthreshold-alpgen_${iPART}.sh
	chmod u+x ${EXPORTDIR}/run_TTbar1Jets_40GeVthreshold-alpgen_${iPART}.sh
	./runjob ${EXPORTDIR}/run_TTbar1Jets_40GeVthreshold-alpgen_${iPART}.sh -N run_TTbar1Jets_40GeVthreshold-alpgen_${iPART}_${TYPE}
	sleep $ST 
done
	
	# STEP 5.B.2 == TTbar_2j-alpgen
	# CREATE JOBS
  	for iPART in `seq 1 22`
	do
      export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTbar2Jets_40GeVthreshold-alpgen"
	sed -e s/MYPART/7TeV_TTbar2Jets_40GeVthreshold-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTbar2Jets_40GeVthreshold-alpgen_${iPART}.sh
	chmod u+x ${EXPORTDIR}/run_TTbar2Jets_40GeVthreshold-alpgen_${iPART}.sh
	./runjob ${EXPORTDIR}/run_TTbar2Jets_40GeVthreshold-alpgen_${iPART}.sh -N run_TTbar2Jets_40GeVthreshold-alpgen_${iPART}_${TYPE}
	sleep $ST 
done

	# STEP 5.B.3 == TTbar_3j-alpgen
	# CREATE JOBS
  	for iPART in `seq 1 11`
	do
      export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTbar3Jets_40GeVthreshold-alpgen"
	sed -e s/MYPART/7TeV_TTbar3Jets_40GeVthreshold-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTbar3Jets_40GeVthreshold-alpgen_${iPART}.sh
	chmod u+x ${EXPORTDIR}/run_TTbar3Jets_40GeVthreshold-alpgen_${iPART}.sh
	./runjob ${EXPORTDIR}/run_TTbar3Jets_40GeVthreshold-alpgen_${iPART}.sh -N run_TTbar3Jets_40GeVthreshold-alpgen_${iPART}_${TYPE}
	sleep $ST 
done
	
	# STEP 5.B.4 == TTbar_4j-alpgen
	# CREATE JOBS
  	for iPART in `seq 1 6`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_TTbar4Jets_40GeVthreshold-alpgen"
	sed -e s/MYPART/7TeV_TTbar4Jets_40GeVthreshold-alpgen/g -e s/MYSUBPART/${iPART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_TTbar4Jets_40GeVthreshold-alpgen_${iPART}.sh
	chmod u+x ${EXPORTDIR}/run_TTbar4Jets_40GeVthreshold-alpgen_${iPART}.sh
	./runjob ${EXPORTDIR}/run_TTbar4Jets_40GeVthreshold-alpgen_${iPART}.sh -N run_TTbar4Jets_40GeVthreshold-alpgen_${iPART}_${TYPE}
	sleep $ST 
	done
fi

#### GAMMA + JETS ####

if [[ $gamma_alpgen -eq 1 ]]
	then echo "Not yet implemented"
fi

if [[ $gamma_madgraph -eq 1 ]]
	then
	# STEP 6.B.1 == PhotonsJets40to100-madgraph
	# CREATE JOBS
	for PART in `seq 1 18`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_PhotonJets40to100-madgraph"
		sed -e s/MYPART/7TeV_PhotonJets40to100-madgraph/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_PhotonJets40to100-madgraph_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_PhotonJets40to100-madgraph_${PART}.sh
		./runjob ${EXPORTDIR}/run_PhotonJets40to100-madgraph_${PART}.sh -N run_PhotonJets40to100-madgraph_${PART}_${TYPE}
		sleep $ST 
	done

	# STEP 6.B.2 == PhotonsJets100to200-madgraph
	# CREATE JOBS
	for PART in `seq 1 8`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_PhotonJets100to200-madgraph"
		sed -e s/MYPART/7TeV_PhotonJets100to200-madgraph/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_PhotonJets100to200-madgraph_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_PhotonJets100to200-madgraph_${PART}.sh
		./runjob ${EXPORTDIR}/run_PhotonJets100to200-madgraph_${PART}.sh -N run_PhotonJets100to200-madgraph_${PART}_${TYPE}
		sleep $ST 
	done

	# STEP 6.B.3 == PhotonsJet200toInf-madgraph
	# CREATE JOBS
	for PART in `seq 1 42`
	do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_PhotonJets200toInf-madgraph"
		sed -e s/MYPART/7TeV_PhotonJets200toInf-madgraph/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_PhotonJets200toInf-madgraph_${PART}.sh
		# SUBMIT JOBS
		chmod u+x ${EXPORTDIR}/run_PhotonJets200toInf-madgraph_${PART}.sh
		./runjob ${EXPORTDIR}/run_PhotonJets200toInf-madgraph_${PART}.sh -N run_PhotonJets200toInf-madgraph_${PART}_${TYPE}
		sleep $ST 
	done
fi

#### InclusivePPmuX ####
if [[ $incppmux -eq 1 ]]
	then
	# STEP 7.A == InclusivePPmuX
        # CREATE JOBS
        for PART in `seq 1 43`
        do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_InclusivePPmuX"
                sed -e s/MYPART/7TeV_InclusivePPmuX/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_InclusivePPmuX_${PART}.sh
                # SUBMIT JOBS
                chmod u+x ${EXPORTDIR}/run_InclusivePPmuX_${PART}.sh
                ./runjob ${EXPORTDIR}/run_InclusivePPmuX_${PART}.sh -N run_InclusivePPmuX_${PART}_${TYPE}
                sleep $ST
        done
fi

#### QCD INCLUSIVE ####
if [[ $incqcd -eq 1 ]]
	then
	# STEP 8.A == QCD_BCtoMu_Pt20
        # CREATE JOBS
        for PART in `seq 1 116`
        do
        export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/7TeV_QCD_BCtoMu_Pt20"
                sed -e s/MYPART/7TeV_QCD_BCtoMu_Pt20/g -e s/MYSUBPART/${PART}/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > ${EXPORTDIR}/run_QCD_BCtoMu_Pt20_${PART}.sh
                # SUBMIT JOBS
                chmod u+x ${EXPORTDIR}/run_QCD_BCtoMu_Pt20_${PART}.sh
                ./runjob ${EXPORTDIR}/run_QCD_BCtoMu_Pt20_${PART}.sh -N run_QCD_BCtoMu_Pt20_${PART}_${TYPE}
                sleep $ST
        done
fi

#if [[ $mytest -eq 1 ]]
#	then
#	 # CREATE JOBS 0_100
#        sed -e s/MYPART/7TeV_TEST/g -e s/MYSUBPART/all/g -e s/MYTYPE/${TYPE}/g background_by_part_subpart.sh > run_TEST_all.sh
#        # SUBMIT JOBS
#        chmod u+x run_TEST_all.sh
#        ./runjob run_TEST_all.sh -N run_TEST_all_${TYPE}
#        sleep $ST
#
#fi

# STEP FINAL
sleep 10
qjob

# Exitting
#rm run_* -f
exit
