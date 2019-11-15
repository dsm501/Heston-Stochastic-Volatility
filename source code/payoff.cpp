//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	payoff.cpp with payoff function definitions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


#include "payoff.h"
#include <algorithm>

double Payoff::Call(double S, double X) //European vanilla call
{
    return std::max(0.0, S - X);
}

double Payoff::Put(double S, double X) //European vanilla put
{
    return std::max(0.0, X-S);
}

double Payoff::LookbackCallFloat(double S_T, double S_min) //European lookkback call with floating strike
{
    return std::max(0.0, S_T-S_min);
}

double Payoff::LookbackCallFixed(double S_max, double X) //European lookback call with with fixed strike
{
    return std::max(0.0, S_max - X);
}

double Payoff::LookbackPutFloat(double S_T, double S_max) //European lookback put with floating strike
{
    return std::max(0.0, S_max - S_T);
}

double Payoff::LookbackPutFixed(double S_min, double X) //European lookback put with fixed strike
{
    return std::max(0.0, X-S_min);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

