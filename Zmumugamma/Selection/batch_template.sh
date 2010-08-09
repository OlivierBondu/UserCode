#!/usr/local/bin/bash
#PBS -l platform=LINUX,u_sps_cmsf     # Plateforme d'execution
#PBS -l T=TIME              # Nombre d'unite normalisee (consommation cpu)
#PBS -q QUEUE
#PBS -l M=MEMORY
#PBS -N NAME               # Job Name
#PBS -o OUTLOG.out
#PBS -e ERRLOG.err

export HOMEDIR=/afs/in2p3.fr/home/o/obondu
source ${HOMEDIR}/361p4.sh

echo "ROOTSYS :"
echo ${ROOTSYS}

echo "LD_LIBRARY_PATH"
echo ${LD_LIBRARY_PATH}

WORKDIR=EXEDIR
echo "Move to WORKDIR ${WORKDIR}"
cd ${WORKDIR}
pwd


echo "Running actual job"
./MACRO

