//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Namespace mc for the Monte-Carlo parameters/functions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#ifndef HESTON_WITH_CLASSES_MONTE_CARLO_H
#define HESTON_WITH_CLASSES_MONTE_CARLO_H

#include "utility.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Struct containing the Monte-Carlo and option data
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace monte_carlo
{

    struct MC_data {
        double S_0; //Initial value of stock at time t=0.
        double r; //Risk free interest rate.
        double sig; //Initial Volatility.

        double X; //Strike price.
        double T; //Expiry date (years).

        long M; //Number of sample paths.
        long N; //Number of time steps.
    };

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Prototype functions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    void ReadInMonteCarloData(MC_data & dat, double S_0, double r, double sig, double X, double T, long M, long N ); //Read in the Monte-Carlo data
    void Accumulate(double val, double & acc_vals, double & acc_squs); //Accumulates payoffs and squared payoffs
    void ComputeValues(MC_data dat, double acc_vals, double acc_squs,  double discount, double & c, double & se); //Computes option value using discount rate
    void DoOutput(double c, double se, double el_time); //Outputs option value, standard error, and time taken to the console
    double Next_S(double S, double drift, double sgrt); //Calculates the next spot price in the geometric brownian motion model
}

namespace mc = monte_carlo; //alias


#endif //HESTON_WITH_CLASSES_MONTE_CARLO_H

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

