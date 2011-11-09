#!/bin/bash
#cd /sps/cms/obondu/CMSSW_4_2_8__RECO_4_2_8_v2/src/Zmumugamma/Selection/
#list=`find -name "v05_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_PU_S6_START42_V11_closure*.out"`
syntax="Syntax ${0} {sampleName}"
if [[ -z ${1} ]]
then
  echo ${syntax}
#  exit 1
fi

list=$1


for fichier in ${list}
do
	let a+=`grep "TOTALnbMuonsAfterID\[0\]" $fichier | cut -f 2`
	let a2+=`grep "TOTALnbMuonsAfterID\[0\]" $fichier | cut -f 5`
	let b+=`grep "TOTALnbMuonsAfterID\[1\]" $fichier | cut -f 2`
        let b2+=`grep "TOTALnbMuonsAfterID\[1\]" $fichier | cut -f 5`
	let c+=`grep "TOTALnbMuonsAfterID\[2\]" $fichier | cut -f 2`
        let c2+=`grep "TOTALnbMuonsAfterID\[2\]" $fichier | cut -f 5`
	let d+=`grep "TOTALnbMuonsAfterID\[3\]" $fichier | cut -f 2`
        let d2+=`grep "TOTALnbMuonsAfterID\[3\]" $fichier | cut -f 5`
	let e+=`grep "TOTALnbMuonsAfterID\[4\]" $fichier | cut -f 2`
        let e2+=`grep "TOTALnbMuonsAfterID\[4\]" $fichier | cut -f 5`
	let f+=`grep "TOTALnbMuonsAfterID\[5\]" $fichier | cut -f 2`
        let f2+=`grep "TOTALnbMuonsAfterID\[5\]" $fichier | cut -f 5`
	let g+=`grep "TOTALnbMuonsAfterID\[6\]" $fichier | cut -f 2`
        let g2+=`grep "TOTALnbMuonsAfterID\[6\]" $fichier | cut -f 5`
	let h+=`grep "TOTALnbMuonsAfterID\[7\]" $fichier | cut -f 2`
        let h2+=`grep "TOTALnbMuonsAfterID\[7\]" $fichier | cut -f 5`
	let i+=`grep "TOTALnbMuonsAfterID\[8\]" $fichier | cut -f 2`
        let i2+=`grep "TOTALnbMuonsAfterID\[8\]" $fichier | cut -f 5`
	let j+=`grep "TOTALnbMuonsAfterID\[9\]" $fichier | cut -f 2`
        let j2+=`grep "TOTALnbMuonsAfterID\[9\]" $fichier | cut -f 5`
	let k+=`grep "TOTALnbMuonsAfterID\[10\]" $fichier | cut -f 2`
        let k2+=`grep "TOTALnbMuonsAfterID\[10\]" $fichier | cut -f 5`
	let l+=`grep "TOTALnbMuonsAfterID\[11\]" $fichier | cut -f 2`
        let l2+=`grep "TOTALnbMuonsAfterID\[11\]" $fichier | cut -f 5`

	let k+=`grep "TOTALnbDimuonsAfterID\[0\]" $fichier | cut -f 2`
        let k2+=`grep "TOTALnbEventsAfterDimuonID\[0\]" $fichier | cut -f 5`
	let m+=`grep "TOTALnbDimuonsAfterID\[1\]" $fichier | cut -f 2`
        let m2+=`grep "TOTALnbEventsAfterDimuonID\[1\]" $fichier | cut -f 5`
	let n+=`grep "TOTALnbDimuonsAfterID\[2\]" $fichier | cut -f 2`
        let n2+=`grep "TOTALnbEventsAfterDimuonID\[2\]" $fichier | cut -f 5`

	let o+=`grep "TOTALnbPhotonsAfterID\[0\]" $fichier | cut -f 2`
        let o2+=`grep "TOTALnbEventsAfterPhotonID\[0\]" $fichier | cut -f 5`
	let p+=`grep "TOTALnbPhotonsAfterID\[1\]" $fichier | cut -f 2`
        let p2+=`grep "TOTALnbEventsAfterPhotonID\[1\]" $fichier | cut -f 5`
	let q+=`grep "TOTALnbPhotonsAfterID\[2\]" $fichier | cut -f 2`
        let q2+=`grep "TOTALnbEventsAfterPhotonID\[2\]" $fichier | cut -f 5`
	let r1+=`grep "TOTALnbPhotonsAfterID\[3\]" $fichier | cut -f 2`
        let r2+=`grep "TOTALnbEventsAfterPhotonID\[3\]" $fichier | cut -f 5`
	let s+=`grep "TOTALnbPhotonsAfterID\[4\]" $fichier | cut -f 2`
        let s2+=`grep "TOTALnbEventsAfterPhotonID\[4\]" $fichier | cut -f 5`
	let t+=`grep "TOTALnbPhotonsAfterID\[5\]" $fichier | cut -f 2`
        let t2+=`grep "TOTALnbEventsAfterPhotonID\[5\]" $fichier | cut -f 5`

	let u+=`grep "TOTALnbMuMuGammaAfterID\[0\]" $fichier | cut -f 2`
        let u2+=`grep "TOTALnbEventsAfterMuMuGammaID\[0\]" $fichier | cut -f 5`
	let v+=`grep "TOTALnbMuMuGammaAfterID\[1\]" $fichier | cut -f 2`
        let v2+=`grep "TOTALnbEventsAfterMuMuGammaID\[1\]" $fichier | cut -f 5`
	let w+=`grep "TOTALnbMuMuGammaAfterID\[2\]" $fichier | cut -f 2`
        let w2+=`grep "TOTALnbEventsAfterMuMuGammaID\[2\]" $fichier | cut -f 5`
	let x+=`grep "TOTALnbMuMuGammaAfterID\[3\]" $fichier | cut -f 2`
        let x2+=`grep "TOTALnbEventsAfterMuMuGammaID\[3\]" $fichier | cut -f 5`
	let y+=`grep "TOTALnbMuMuGammaAfterID\[4\]" $fichier | cut -f 2`
        let y2+=`grep "TOTALnbEventsAfterMuMuGammaID\[4\]" $fichier | cut -f 5`
	let z+=`grep "TOTALnbMuMuGammaAfterID\[5\]" $fichier | cut -f 2`
        let z2+=`grep "TOTALnbEventsAfterMuMuGammaID\[5\]" $fichier | cut -f 5`
	let alpha+=`grep "TOTALnbMuMuGammaAfterID\[6\]" $fichier | cut -f 2`
        let alpha2+=`grep "TOTALnbEventsAfterMuMuGammaID\[6\]" $fichier | cut -f 5`

	let beta+=`grep "TOTALnbMuMuGammaAfterID\[7\]" $fichier | cut -f 2`
        let beta2+=`grep "TOTALnbEventsAfterMuMuGammaID\[7\]" $fichier | cut -f 5`

done  
echo "${a},${a2}"
echo "${b},${b2}"
echo "${c},${c2}"
echo "${d},${d2}"
echo "${e},${e2}"
echo "${f},${f2}"
echo "${g},${g2}"
echo "${h},${h2}"
echo "${i},${i2}"
echo "${j},${j2}"
echo ","
echo "${k},${k2}"
echo "${l},${l2}"
echo "${m},${m2}"
echo "${n},${n2}"
echo ","
echo "${o},${o2}"
echo "${p},${p2}"
echo "${q},${q2}"
echo "${r1},${r2}"
echo "${s},${s2}"
echo "${t},${t2}"
echo ","
echo "${u},${u2}"
echo "${v},${v2}"
echo "${w},${w2}"
echo "${x},${x2}"
echo "${y},${y2}"
echo "${z},${z2}"
echo "${alpha},${alpha2}"
echo ","
echo "${beta},${beta2}"


#TOTALnbMuonsAfterID[0]= 751371          TOTALnbEventsAfterMuonID[0]=    249999 exemple de ligne a extraire
