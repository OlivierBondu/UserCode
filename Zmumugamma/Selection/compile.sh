#!/bin/bash
syntax="Syntax ${0} {executableName}"
if [[ -z ${1} ]]
then
  echo ${syntax}
#  exit 1
fi
exeFile=${1}



g++ Selection_miniTree.C -L`pwd` -lToto `root-config --libs --cflags` -o ${exeFile}


