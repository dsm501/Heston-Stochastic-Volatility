//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	monte_carlo.cpp  with monte-carlo function definitions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <iostream>
#include "rv_library.h"
#include "utility.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include "monte_carlo.h"
#include "payoff.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Read in the user specified Monte-Carlo and option data
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void monte_carlo::ReadInMonteCarloData(MC_data &dat, double S_0, double r, double sig, double X, double T, long M,
        long N)
{
    dat.S_0 = S_0; //Initial value of stock at time t=0
    dat.r = r; //Risk free interest rate
    dat.sig = sig; //initial volatility

    dat.X = X; //Strike price
    dat.T = T; //Expiry date

    dat.M = M; //Number of sample paths
    dat.N = N; //Number of time steps
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Calculate the next spot value for geometric Brownian motion
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
double monte_carlo::Next_S(double S, double drift, double sgrt)
{
    double w = rv::GetNormalVariate();
    return S*std::exp(drift + sgrt*w);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Accumlate the payoffs and squared payoffs
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void monte_carlo::Accumulate(double val, double &acc_vals, double &acc_squs)
{
    acc_vals += val;
    acc_squs += val*val;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	ComputeValues computes option value using the discount rate
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void monte_carlo::ComputeValues(MC_data dat, double acc_vals, double acc_squs, double discount, double &c, double &se)
{
    c = discount*acc_vals/dat.M;
    se = discount*std::sqrt(acc_squs - acc_vals*acc_vals/dat.M)/dat.M;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Output option value, standard error, and time taken to the console
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void monte_carlo::DoOutput(double c, double se, double el_time)
{
    ut::OutputLine("Option value ", c);
    ut::OutputLine("se           ", se);
    ut::OutputLine("time taken   ", el_time);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



