#! /usr/local/bin/bash -l
#$ -l ct=10000
#$ -P P_cmsf
#$ -l vmem=3G
#$ -l fsize=10G
#$ -q medium
#$ -l sps=1
##$ -l dcache=1
#$ -N PileUp_S6
### Merge the stdout et stderr in a single file
#$ -j y
### fichiers .e et .o copied to current working directory
#$ -cwd
##$ -m be
### set array job indices 'min-max:interval'
#$ -t 1-50

syntax="${0} {parameter}"
#if [[ -z ${6} ]]
#if [[ -z ${2} ]]
#then
#	echo ${syntax}
#	exit 1
#fi

ijob=`echo "${SGE_TASK_ID} - 1" | bc -ql`

echo "USER=${USER}"

# LOAD CORRECT ENVIRONMENT VARIABLES FROM SPS
echo "LOAD CORRECT ENVIRONMENT VARIABLES FROM SPS"
export HOMEDIR=/afs/in2p3.fr/home/s/sgandurr
source ${HOMEDIR}/428p7.sh
SPSDIR=`pwd`
WORKDIR=${TMPDIR}

echo "USER=${USER}"

# CHECK THE ENVIRONMENT VARIABLES
echo "CHECK THE ENVIRONMENT VARIABLES"
echo "ROOTSYS :"
echo ${ROOTSYS}
echo ""

echo "USER=${USER}"

cd ${TMPDIR}/
echo "pwd; ls -als"
pwd; ls -als
echo ""

# COPY HEADER FILES TO WORKER
echo "COPY HEADER FILES TO WORKER"
#mkdir ${TMPDIR}/interface
#cp ${SPSDIR}/UserCode/IpnTreeProducer/interface/*h ${TMPDIR}/interface/
if [[ ! -e ${TMPDIR}/interface ]]
then
  mkdir ${TMPDIR}/interface
	cp ${SPSDIR}/UserCode/IpnTreeProducer/interface/*h ${TMPDIR}/interface/
fi

echo "USER=${USER}"

# COPY IpnTree LIB FILE TO WORKER
#mkdir ${TMPDIR}/lib
#cp ${SPSDIR}/UserCode/IpnTreeProducer/src/libToto.so ${TMPDIR}/lib/
echo "COPY IpnTree LIB FILE TO WORKER"
if [[ ! -e ${TMPDIR}/lib ]]
then
	mkdir ${TMPDIR}/lib
	cp ${SPSDIR}/UserCode/IpnTreeProducer/src/libToto.so ${TMPDIR}/lib/
fi

echo "USER=${USER}"

cp ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/listFiles_* ${TMPDIR}/

# ADD CURRENT DIRECTORY AND LIB TO LIRARY PATH
LD_LIBRARY_PATH=`echo "${LD_LIBRARY_PATH}:${WORKDIR}/lib:${WORKDIR}"`
echo "LD_LIBRARY_PATH"
echo ${LD_LIBRARY_PATH}
echo ""

echo "USER=${USER}"

# COPY EXECUTABLE TO WORKER
echo "COPY EXECUTABLE TO WORKER"
cp ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/pileUp_getNvtxRECO.exe ${TMPDIR}/

echo "pwd; ls -als"
pwd; ls -als
echo ""

echo "USER=${USER}"

# EXECUTE JOB
echo "EXECUTE JOB"
cd ${TMPDIR}/
#./pileUp_getNvtxRECO.exe ${1} ${2} ${3} ${4} ${5} ${6} 2> ${2}.err | tee ${2}.out
./pileUp_getNvtxRECO.exe ${1} ${1} 50 ${ijob} 1 2> pileUp_${1}_part${ijob}.err | tee pileUp_${1}_part${ijob}.out

echo "pwd; ls -als"
pwd; ls -als
echo ""

# GET BACK OUTPUT FILES TO SPS
echo "GET BACK OUTPUT FILES TO SPS AND REMOVE THEM FROM DISTANT DIR"
mv ${TMPDIR}/miniTree_pileUp_${1}_part${ijob}*root ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/
mv ${TMPDIR}/pileUp_${1}_part${ijob}*out ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/
mv ${TMPDIR}/pileUp_${1}_part${ijob}*err ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/
rm ${TMPDIR}/pileUp_getNvtxRECO.exe

#"cd ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/"
#cd ${SPSDIR}/Zmumugamma_miniTrees_rereco_2011_lastTag/
#echo "pwd; ls -als"
#pwd; ls -als
#echo ""



exit 0
