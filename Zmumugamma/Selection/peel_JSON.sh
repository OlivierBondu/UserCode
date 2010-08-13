#!/bin/bash
# Script to extract run numbers from a JSON file, in order to lauch one (IpnTreeProducer) crab job per run (to get rid of trigger trouble)
# Written by O. Bondu (July 2010)

syntax="Syntax ${0} {JSON file}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

JSONfile=${1}

cat ${JSONfile} | sed -e "s/\:/\n/g" | 'grep' \" | awk -F\" '{print $2}'

exit 0
