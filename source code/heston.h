//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Namespace heston for the heston model parameters/functions. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


#include <iostream>
#include "rv_library.h"
#include "utility.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include "monte_carlo.h"

#ifndef HESTON_WITH_CLASSES_HESTON_H
#define HESTON_WITH_CLASSES_HESTON_H

namespace heston
{

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Structure containing the Heston model parameters.
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    struct Heston_data
    {
        double kappa; // volatility mean reversion rate
        double vol_of_vol; // volatility of volatility
        double rho; // Correlation between the Brownian motions
        double theta; // Long run average volatility
    };

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Prototype functions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    void volatility_path(const std::vector<double> & vol_draws, std::vector<double> & vol_path, mc::MC_data mc,
            Heston_data heston); //Compute the volatility path
    void stock_path(const std::vector<double> & spot_draws, const std::vector<double> & vol_path,
            std::vector<double> & spot_path, mc::MC_data mc); //Compute the stock price path

    void ReadInHestonData(Heston_data & heston, double rho, double vol_of_vol, double kappa, double theta); //Assign values to the Heston model parameters

}

#endif //HESTON_WITH_CLASSES_HESTON_H

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

