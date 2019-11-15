//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	heston.cpp with heston function definitions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "heston.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// calculate volatility path
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void heston::volatility_path(const std::vector<double> &vol_draws,
        std::vector<double> &vol_path,
        mc::MC_data mc,
        heston::Heston_data heston)
{
    size_t size =  vol_draws.size();
    double dt = mc.T/mc.N;

    for (size_t i=0; i<size-1; i++) {
        double max = std::max(vol_path[i], 0.0);
        vol_path[i+1] = vol_path[i] + heston.kappa * dt * (heston.theta - max) +
                heston.vol_of_vol * sqrt(max * dt) * vol_draws[i];
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// calculate stock path
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void heston::stock_path(const std::vector<double> &spot_draws, const std::vector<double> &vol_path,
        std::vector<double> &spot_path, mc::MC_data mc)
{
    size_t size = spot_draws.size();
    double dt = mc.T/mc.N;

    for (size_t i=0; i<size-1; i++) {
        double max = std::max(vol_path[i], 0.0);
        spot_path[i+1] = spot_path[i] * exp( (mc.r - 0.5*max)*dt +
                                             sqrt(max*dt)*spot_draws[i]);
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Read in the heston data
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void heston::ReadInHestonData(heston::Heston_data &heston, double rho, double vol_of_vol, double kappa, double theta)
{
    heston.rho = rho; //Correlation of Brownian motions
    heston.vol_of_vol = vol_of_vol; //Volatility of volatility
    heston.kappa = kappa; //Volatility mean reversion rate
    heston.theta = theta; //Long run average volatility
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

