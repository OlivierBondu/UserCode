#!/bin/bash
# Script de lancement de jobs cmsRun
# Created by Clement Baty
# Modified by Olivier Bondu (October 2009)
# Adapted for 3_1_4 (January 2010)
# Adapted for 336 (February 2010)

CMSSWRelease="CMSSW_3_5_7"
DATE="`date +%d-%m-%y_%Hh%M:%S`"

export TYPE="MYTYPE"
export PART="MYPART"
export CLEMPART="MYPART"
export SUBPART="MYSUBPART"
export TYPENAME=`echo ${TYPE} | sed -e "s,-,_,"`
RawSampleName=`echo ${PART} | cut -d _ -f 2-`
Energy=`echo ${PART} | cut -d _ -f -1`

echo "------------------------------------------------------------------------------------------------------"
echo  Batch job started at ${DATE} for `whoami` on `hostname` for ${PART}/${SUBPART} with file ${FILE} 
echo "------------------------------------------------------------------------------------------------------"


# Prepare environnement
#source /afs/in2p3.fr/grid/profiles/lcg_env.sh
#source $VO_CMS_SW_DIR/cmsset_default.sh
source /afs/in2p3.fr/home/o/obondu/336.sh
export CMSSWDIR="/sps/cms/obondu/${CMSSWRelease}/src"
export RECODIR="/sps/cms/obondu/${CMSSWRelease}/src/Zmumugamma/RecoSamples/${PART}"
export LOCALDIR="/sps/cms/obondu/${CMSSWRelease}/src/Zmumugamma/Selection"
export FILE="${LOCALDIR}/SVG/ClemAnalysis_${TYPENAME}.C"
export WORKDIR="`pwd`"
export EXPORTDIR="${LOCALDIR}/Analysis/${TYPE}/${PART}"

# Set Correct environnement !
cd ${CMSSWDIR}
echo "Using ${CMSSWRelease}"
eval `scram runtime -sh`

# Copy needed files
#cd ${RECODIR}

# MODIFY SVG/ClemAnalysis.C to Analysis/TYPE/PART/run_ClemAnalysis_X_Y.C
# STEP 1 CREATE the RUN.C 

CLEMPART="`echo ${PART} | sed s/-/_/g`"
START="`ls ${RECODIR}/Toto_${PART}_* | cut -d _ -f 5- |cut -d . -f -1  | sort -n | head -n 2 | tail -n 1`"
END="`ls ${RECODIR}/Toto_${PART}_* | cut -d _ -f 5- |cut -d . -f -1  | sort -n | tail -n 1`"
NBFILES="$((END - START +1))"
NBFILESTRUE="`ls ${RECODIR}/Toto_${PART}_* | wc -l`"

if [[ -n ${START} && -n ${END} ]]
	then echo "Running part ${PART} with ${NBFILES} files (precalculate) and ${NBFILESTRUE} (calculate)"	
	else echo "No files, aborting" && exit
fi

### PART Zmumugamma
if [[ ${RawSampleName} = "Zmumugamma" ]]
	then
	if [[ ${RawSampleName} = "Zmumugamma" ]] # Zmumugamma
		then
		sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/1/g -e s/FIN/2/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s/ClemAnalysis/run_ClemAnalysis_${PART}_${SUBPART}/g -e /outputfile/s/s.root/s_${SUBPART}.root/g -e /SIGNAL/s/false/true/g ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C 
	fi

fi

### PART MADGRAPH

if [[ ${RawSampleName} = "ZJets-madgraph" ]]
	then
	sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/$((SUBPART * 2 - 1))/g -e s/FIN/$((SUBPART * 2))/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s,ClemAnalysis,run_ClemAnalysis_${CLEMPART}_${SUBPART},g -e /outputfile/s/s.root/s_${SUBPART}.root/g -e /NEED_ZJETS_VETO/s/false/true/g ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C 
fi

### PART Z + M JETS ALPGEN

if [[ `echo ${RawSampleName} | grep Z.Jets` ]]
	then
	if [[ ${SUBPART} = "all" ]] ; then MYSUBPART=1 ; else MYSUBPART=${SUBPART} ; fi 
	sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/$((MYSUBPART * 2 - 1))/g -e s/FIN/$((MYSUBPART * 2))/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s,ClemAnalysis,run_ClemAnalysis_${CLEMPART}_${SUBPART},g -e /outputfile/s/s.root/s_${SUBPART}.root/g -e /NEED_ZJETS_VETO/s/false/true/g ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C
fi

### PART W + M JETS ALPGEN and TTbar (ALPGEN/MADGRAPH) and PhotonsJets (ALPGEN/MADGRAPH) 

if [[ `echo ${RawSampleName} | grep W.Jets` || `echo ${RawSampleName} | grep TTbar` || `echo ${RawSampleName} | grep PhotonJets` || `echo ${RawSampleName} | grep Gamma.Jets` ]]
	then
	if [[ ${SUBPART} = "all" ]] ; then MYSUBPART=1 ; else MYSUBPART=${SUBPART} ; fi 
	sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/$((MYSUBPART * 2 - 1))/g -e s/FIN/$((MYSUBPART * 2))/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s,ClemAnalysis,run_ClemAnalysis_${CLEMPART}_${SUBPART},g -e /outputfile/s/s.root/s_${SUBPART}.root/g  ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C
fi

### PART InclusiveBMuPt15 and InclusivePPmuX 

if [[ ${RawSampleName} = "InclusiveMuPt" || ${RawSampleName} = "InclusivePPmuX" ]]
        then
        sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/$((SUBPART * 2 - 1))/g -e s/FIN/$((SUBPART * 2))/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s,ClemAnalysis,run_ClemAnalysis_${CLEMPART}_${SUBPART},g -e /outputfile/s/s.root/s_${SUBPART}.root/g ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C
fi 

### PART QCD_BCtoMu_Pt20

if [[ ${RawSampleName} = "QCD_BCtoMu_Pt20" ]]
	then
        sed -e s,RECODIR,${RECODIR},g -e s/DEBUT/$((SUBPART))/g -e s/FIN/$((SUBPART))/g -e s,EXPORTDIR,${EXPORTDIR},g -e s/PART/${PART}/g -e s,ClemAnalysis,run_ClemAnalysis_${CLEMPART}_${SUBPART},g -e /outputfile/s/s.root/s_${SUBPART}.root/g ${FILE} > ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C
fi

##### END OF WRITING EVENTS #####

export NEED=1

# STEP 2 CREATE the TEMPLATE file
echo ".L ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C" > ${EXPORTDIR}/template_${PART}_${SUBPART}
if [[ $NEED -eq 1 ]] ; then echo ".O 0" >> ${EXPORTDIR}/template_${PART}_${SUBPART} ; fi
echo "run_ClemAnalysis_${CLEMPART}_${SUBPART}()" >> ${EXPORTDIR}/template_${PART}_${SUBPART}
echo ".q" >> ${EXPORTDIR}/template_${PART}_${SUBPART}
	

# Execute the program :
echo "Starting the program"
	root.exe < ${EXPORTDIR}/template_${PART}_${SUBPART} 2> ${EXPORTDIR}/errlog_sample_${PART}_${SUBPART}.log | tee ${EXPORTDIR}/outlog_sample_${PART}_${SUBPART}.log 
echo "Ending the program"

# End of the program :
echo  "----------------------------"
echo  "Script work done at `date +%d-%m-%y_%Hh%M:%S`"
echo  "----------------------------"

# Copying relevant files to local
#mkdir -p ${LOCALDIR}/${EXPORTDIR}
echo "Moving files from temp working directory to local"
gzip ${EXPORTDIR}/*log_sample_${PART}_${SUBPART}.log -f # GZIP LOG FILES
#mv -f *_${PART}_${SUBPART}.root ${LOCALDIR}/${EXPORTDIR} # ROOT FILE
#mv -f *log_sample_${PART}_${SUBPART}.log.gz ${LOCALDIR}/${EXPORTDIR} # LOG FILES
#mv -f ${EXPORTDIR}/template_${PART}_${SUBPART} ${EXPORTDIR}/run_ClemAnalysis_${CLEMPART}_${SUBPART}.C ${LOCALDIR}/${EXPORTDIR} # HELPER FILES
mv -f outfile_run_${PART}_${SUBPART}.log ${EXPORTDIR}

# Successfull exit
#echo "Well done Commander !"
exit 0

