// Function coded by Louis Sgandurra & Olivier Bondu
// From a code excerpt of Jan Veverka (http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/JanVeverka/JPsi/MuMu/src/ModalInterval.cc?revision=1.12&view=markup)
// November 2011                                           
#include <vector>

void FindRange(double pourcentage, TTree * chain, string temp, double * MinRange, double * MaxRange, string varName)
{

	int n = chain->Draw(varName.c_str(), temp.c_str(), "goff");
	double *vect = chain->GetV1();
	vector<double> VarVector;
	for( int idx=0 ; idx < n ; idx++ ) VarVector.push_back(vect[idx]);
	sort(VarVector.begin(), VarVector.end());

	size_t interval_entries = TMath::Ceil(pourcentage * n);
	cout << "interval_entries= " << interval_entries << endl;

	vector<double>::iterator lower = VarVector.begin();
	vector<double>::iterator upper = VarVector.begin() + interval_entries - 1;
	double dx = *upper - *lower;
	cout << "dx= " << dx << endl;

	for(vector<double>::iterator first = lower, last = upper; last < VarVector.end(); first++, last++)
	{
		if((*last - *first) < dx)
		{

			lower = first;
			upper = last;
			dx = *upper - *lower;
			//cout<<endl<<"dx into the loop = "<<dx;
		}
	}
        *MinRange = *lower;
        *MaxRange = *upper;
return;
}

