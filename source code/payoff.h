//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Namespace payoff, for payoff functions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#ifndef HESTON_PAYOFF_H
#define HESTON_PAYOFF_H

namespace Payoff
{
    extern double S; //Spot price
    extern double S_min; //Minimum spot price
    extern double S_max; //Maximum spot price
    extern double S_T; //Spot price at expiry
    extern double X; //Strike price

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Prototype functions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    double Call(double S, double X);
    double Put(double S, double X);
    double LookbackCallFloat(double S, double S_min);
    double LookbackCallFixed(double S_max, double X);
    double LookbackPutFloat(double S_T, double S_max);
    double LookbackPutFixed(double S_min, double X);
}

namespace pf = Payoff; //alias

#endif //HESTON_PAYOFF_H

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

