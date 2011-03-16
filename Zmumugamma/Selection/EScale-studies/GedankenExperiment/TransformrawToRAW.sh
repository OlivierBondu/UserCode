#!/bin/bash
# macro to convert raw dump into RAW (k, category) <-> (int, int) mapping
# written by O. Bondu (February 2011)

type="data"

cp ${type}.raw ${type}.RAW

if [[ "${type}" == "data" ]]
then
	sed -i -e "s/data/0/g" ${type}.RAW
fi

sed -i -e "s/EBEE/0/g" ${type}.RAW
sed -i -e "s/EB_10_LT_eta_LT_144/12/g" ${type}.RAW
sed -i -e "s/EB_05_LT_eta_LT_10/11/g" ${type}.RAW
sed -i -e "s/EB_eta_LT_05/10/g" ${type}.RAW
sed -i -e "s/EEM_ES/14/g" ${type}.RAW
sed -i -e "s/EEP_ES/13/g" ${type}.RAW
sed -i -e "s/EB_unconv_ntracks/19/g" ${type}.RAW
sed -i -e "s/EB_conv_ntracks/20/g" ${type}.RAW
sed -i -e "s/EE_unconv_ntracks/21/g" ${type}.RAW
sed -i -e "s/EE_conv_ntracks/22/g" ${type}.RAW
sed -i -e "s/EB_unconv/15/g" ${type}.RAW
sed -i -e "s/EB_conv/16/g" ${type}.RAW
sed -i -e "s/EE_unconv/17/g" ${type}.RAW
sed -i -e "s/EE_conv/18/g" ${type}.RAW
sed -i -e "s/EBMref/7/g" ${type}.RAW
sed -i -e "s/EBPref/6/g" ${type}.RAW
sed -i -e "s/EEM/9/g" ${type}.RAW
sed -i -e "s/EEP/8/g" ${type}.RAW
sed -i -e "s/EBref/5/g" ${type}.RAW
sed -i -e "s/EBP/3/g" ${type}.RAW
sed -i -e "s/EBM/4/g" ${type}.RAW
sed -i -e "s/EB/1/g" ${type}.RAW
sed -i -e "s/EE/2/g" ${type}.RAW

sed -i -e "s/ik_SCraw/7/g" ${type}.RAW
sed -i -e "s/k_SCraw/6/g" ${type}.RAW
sed -i -e "s/s_SCraw/8/g" ${type}.RAW
sed -i -e "s/ik_SC/4/g" ${type}.RAW
sed -i -e "s/k_SC/3/g" ${type}.RAW
sed -i -e "s/s_SC/5/g" ${type}.RAW
sed -i -e "s/ik_5x5/10/g" ${type}.RAW
sed -i -e "s/k_5x5/9/g" ${type}.RAW
sed -i -e "s/s_5x5/11/g" ${type}.RAW
sed -i -e "s/ik/1/g" ${type}.RAW
sed -i -e "s/k/0/g" ${type}.RAW
sed -i -e "s/s/2/g" ${type}.RAW

sed -i -e "/inf/d" ${type}.RAW
sed -i -e "/nan/d" ${type}.RAW

exit 0
