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

	if( correctionSet == "Louis" )
        {
                if(isEB)
                {
                        param.push_back(0.7);
                        param.push_back(4.9);
                        param.push_back(-0.001492);
                        param.push_back(0.0001637);
                        param.push_back(1.003);
                        param.push_back(-0.03081);
                        param.push_back(136.7);
                } else {
                        param.push_back(0.8);
                        param.push_back(4.5);
                        param.push_back(-0.0004003);
                        param.push_back(0.003938);
                        param.push_back(0.9638);
                        param.push_back(-0.07402);
                        param.push_back(30.52);
                }
        }

	if( correctionSet == "Anne-Fleur" )
        {
                if(isEB)
                {
                        param.push_back(1.1);
                        param.push_back(8.0);
                        param.push_back(-0.002362);
                        param.push_back(0.004314);
                        param.push_back(1.001);
                        param.push_back(0.0003413);
                        param.push_back(3.124);
                } else {
                        param.push_back(0.9);
                        param.push_back(6.5);
                        param.push_back(-0.07667);
                        param.push_back(0.1407);
                        param.push_back(0.9157);
                        param.push_back(0.00251);
                        param.push_back(1.117);
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

	if( correctionSet == "Louis" )
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


	if( correctionSet == "Anne-Fleur" ) 
  	{
    		if(isEB)//need to verify
    		{
                        param.push_back(0.9963);
                        param.push_back(-0.1158);
                        param.push_back(-4.189);
                        param.push_back(0.0000000000);
                        param.push_back(0.0000000000);
                        param.push_back(0.9009);
                        param.push_back(39.67);
                        param.push_back(1.253);
                        param.push_back(7.6);
                        param.push_back(1.081);
                        param.push_back(-0.00181);
                } else {
                        param.push_back(-1.513);
                        param.push_back(-0.4142);
                        param.push_back(1.239);
                        param.push_back(0.2625);
                        param.push_back(-0.2016);
                        param.push_back(-0.02905);
                        param.push_back(1.7);
                        param.push_back(0.0000000000);
                        param.push_back(1.0000000000);//not sure
                        param.push_back(0.0000000000);
                        param.push_back(0.0000000000);
                }
        }

}

