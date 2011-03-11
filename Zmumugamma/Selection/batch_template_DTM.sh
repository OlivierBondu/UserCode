#!/usr/local/bin/bash
##PBS -o OUTLOG.out
##PBS -e ERRLOG.err

syntax="${0} {parameter}"
if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi

echo "USER=${USER}"

# LOAD CORRECT ENVIRONMENT VARIABLES FROM SPS
echo "LOAD CORRECT ENVIRONMENT VARIABLES FROM SPS"
export HOMEDIR=/afs/in2p3.fr/home/o/obondu
source ${HOMEDIR}/386v6.sh
SPSDIR=`pwd`
WORKDIR=${TMPBATCH}

echo "USER=${USER}"

# CHECK THE ENVIRONMENT VARIABLES
echo "CHECK THE ENVIRONMENT VARIABLES"
echo "ROOTSYS :"
echo ${ROOTSYS}
echo ""

echo "USER=${USER}"

cd ${TMPBATCH}/
echo "pwd; ls -als"
pwd; ls -als
echo ""

# COPY HEADER FILES TO WORKER
echo "COPY HEADER FILES TO WORKER"
#mkdir ${TMPBATCH}/interface
#cp ${SPSDIR}/UserCode/IpnTreeProducer/interface/*h ${TMPBATCH}/interface/
if [[ ! -e ${TMPBATCH}/interface ]]
then
  mkdir ${TMPBATCH}/interface
	cp ${SPSDIR}/UserCode/IpnTreeProducer/interface/*h ${TMPBATCH}/interface/
fi

echo "USER=${USER}"

# COPY IpnTree LIB FILE TO WORKER
#mkdir ${TMPBATCH}/lib
#cp ${SPSDIR}/UserCode/IpnTreeProducer/src/libToto.so ${TMPBATCH}/lib/
echo "COPY IpnTree LIB FILE TO WORKER"
if [[ ! -e ${TMPBATCH}/lib ]]
then
	mkdir ${TMPBATCH}/lib
	cp ${SPSDIR}/UserCode/IpnTreeProducer/src/libToto.so ${TMPBATCH}/lib/
fi

echo "USER=${USER}"

# ADD CURRENT DIRECTORY AND LIB TO LIRARY PATH
LD_LIBRARY_PATH=`echo "${LD_LIBRARY_PATH}:${WORKDIR}/lib:${WORKDIR}"`
echo "LD_LIBRARY_PATH"
echo ${LD_LIBRARY_PATH}
echo ""

echo "USER=${USER}"

# COPY EXECUTABLE TO WORKER
echo "COPY EXECUTABLE TO WORKER"
cp ${SPSDIR}/Zmumugamma/Selection/LOCATION/MACRO ${TMPBATCH}/

echo "pwd; ls -als"
pwd; ls -als
echo ""

echo "USER=${USER}"

# EXECUTE JOB
echo "EXECUTE JOB"
cd ${TMPBATCH}/
./MACRO ${1}

echo "pwd; ls -als"
pwd; ls -als
echo ""

# GET BACK OUTPUT FILES TO SPS
echo "GET BACK OUTPUT FILES TO SPS AND REMOVE THEM FROM DISTANT DIR"
mv ${TMPBATCH}/miniTree_SAMPLEPART_${1}*root ${SPSDIR}/Zmumugamma/Selection/LOCATION/
mv ${TMPBATCH}/SAMPLEPART_${1}*out ${SPSDIR}/Zmumugamma/Selection/LOCATION/
mv ${TMPBATCH}/SAMPLEPART_${1}*err ${SPSDIR}/Zmumugamma/Selection/LOCATION/
rm ${TMPBATCH}/MACRO

"cd ${SPSDIR}/Zmumugamma/Selection/LOCATION/"
cd ${SPSDIR}/Zmumugamma/Selection/LOCATION/
echo "pwd; ls -als"
pwd; ls -als
echo ""



exit 0
