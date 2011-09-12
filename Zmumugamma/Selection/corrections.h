void parameters_Ceta(vector<double> &param, string correctionSet)
{
	param.push_back(40.2197990417);
	param.push_back(-0.0000030310);
//	return param;
}


void parameters_fbrem(vector<double> &param, string correctionSet, bool isEB)
{
	if( correctionSet == "START42_V11" )
	{
		if(isEB)
		{
			param.push_back(1.1000000238);
			param.push_back(8.0000000000);
			param.push_back(-0.0528899990);
			param.push_back(0.1374000013);
			param.push_back(0.9140999913);
			param.push_back(-0.0006690000);
			param.push_back(1.3799999952);
		} else {
			param.push_back(0.8999999762);
			param.push_back(6.5000000000);
			param.push_back(-0.0794499964);
			param.push_back(0.1298000067);
			param.push_back(0.9146999717);
			param.push_back(-0.0015650000);
			param.push_back(0.8999999762);
		}
	}
}

void parameters_feteta(vector<double> &param, string correctionSet, bool isEB)
{
  if( correctionSet == "START42_V11" )
  {
    if(isEB)
    {
			param.push_back(1.0000000000);
			param.push_back(-0.6980000138);
			param.push_back(0.0000000000);
			param.push_back(0.0000000000);
			param.push_back(0.0000000000);
			param.push_back(0.6604999900);
			param.push_back(8.8249998093);
			param.push_back(0.8410000205);
			param.push_back(7.5999999046);
			param.push_back(1.0809999704);
			param.push_back(-0.0018100000);
		} else {
			param.push_back(-3.5160000324);
			param.push_back(-2.3619999886);
			param.push_back(2.1510000229);
			param.push_back(1.5720000267);
			param.push_back(-0.3359999955);
			param.push_back(-0.2806999981);
			param.push_back(3.2000000477);
			param.push_back(0.0000000000);
			param.push_back(1.0000000000);
			param.push_back(0.0000000000);
			param.push_back(0.0000000000);
		}
	}
}

