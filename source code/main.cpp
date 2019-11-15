
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main.cpp. 1423101
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
#include "heston.h"
#include "rv_library.h"
#include "utility.h"
#include "payoff.h"
#include "monte_carlo.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main() {
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Initialise structs and parameters and then open the Input Data.txt file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    heston::Heston_data heston; //Heston data struct to hold the heston parameters
    mc::MC_data mc; //Monte-Carlo data struct to hold the Monte-Carlo and option data
    double rho, vol_of_vol, kappa, theta; //Heston model parameters
    double S_0, r, sig, X, T; //Option data
    long M, N; //Monte-Carlo data
    std::string option, option_type, model, model_type;
    std::ifstream file_("Input Data.txt"); //Input file
    if(file_.is_open())
    {
        while(file_ >> rho >> vol_of_vol >> kappa >> theta >> S_0 >> r >> sig >> X >> T >> M >> N >> option >> model)
        {
            heston::ReadInHestonData(heston, rho, vol_of_vol, kappa, theta); //Read in the first line of Input Data.txt into the heston struct
            mc::ReadInMonteCarloData(mc, S_0, r, sig, X, T, M, N);  //Read in the second line of the
            option_type = option; //Set the option_type string to the option type specified by the user
            model_type = model; //Set the model_type string to the model type specified by the user
        }
        file_.close(); //close the file
    }
    else
        throw std::runtime_error("File cannot be opened"); //Throw an error if the file could not be opened


    double acc_vals = 0; //Store payoffs for heston
    double acc_squs = 0; //Store squared payoffs for heston
    double acc_vals_2 = 0; //Store payoffs for gbm
    double acc_squs_2 = 0; //Store squared payoffs for gbm



    std::vector<double> spot_draws(mc.N, 0.0); //Create vector for spot normal draws
    std::vector<double> vol_draws(mc.N, 0.0); //Create vector for vol normal draws
    std::vector<double> spot_prices(mc.N, mc.S_0); //Create vector for the spot prices
    std::vector<double> vol_prices(mc.N, mc.sig); //Create vector for the vol prices

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  if statement executed if the user chooses heston
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    double st_time = clock();

    if(model_type == "heston") {

         ut::OutputLine("Heston Model");
         for (long j = 1; j <= mc.M; ++j) {

             for (int i = 0; i < mc.N-1; i++) //Generating the vector of correlated normal random variables
             {
                 double y_1 = rv::GetNormalVariate();
                 double y_2 = rv::GetNormalVariate();
                 double x_1 = y_1;
                 double x_2 = heston.rho * y_1 + sqrt(1 - heston.rho * heston.rho) * y_2;
                 spot_draws[i] = x_1; //Storing the random variables for stock paths in a vector
                 vol_draws[i] = x_2; //Storing the random variables for vol path in a vector
             }

             ut::OutputCounter(j, mc.M, 50000);
             heston::volatility_path(vol_draws, vol_prices, mc, heston);
             heston::stock_path(spot_draws, vol_prices, spot_prices, mc);

             double S_min = *std::min_element(spot_prices.begin(), spot_prices.end()); //Minimum value of the stock over the stock path
             double S_max = *std::max_element(spot_prices.begin(), spot_prices.end()); //Maximum value of the stock over the stock path

             double payoff;
             if (option_type == "Call") {
                 payoff = pf::Call(spot_prices[mc.N - 1], mc.X); //Payoff for call option
             } else if (option_type == "Put") {
                 payoff = pf::Put(spot_prices[mc.N - 1], mc.X); //Payoff for put option
             } else if (option_type == "LookbackCallFixedStrike") {
                 payoff = pf::LookbackCallFixed(S_max, mc.X); //Payoff for a lookback call with fixed strike
             } else if (option_type == "LookbackCallFloatingStrike") {
                 payoff = pf::LookbackCallFloat(spot_prices[mc.N - 1], S_min); //Payoff for a lookback call with floating strike
             } else if (option_type == "LookbackPutFixedStrike") {
                 payoff = pf::LookbackPutFixed(S_min, mc.X); //Payoff for a lookback put with fixed strike
             } else if (option_type == "LookbackPutFloatingStrike") {
                 payoff = pf::LookbackPutFloat(spot_prices[mc.N - 1], S_max); //Payoff for a lookback put with floating strike
             }

             mc::Accumulate(payoff, acc_vals, acc_squs); //Accumulate payoffs and squared payoffs

         }

         //Do output for the Heston model
         double discount = std::exp(-mc.r * mc.T); //Discount rate
         double c;  //Option value
         double se; //Option standard error
         mc::ComputeValues(mc, acc_vals, acc_squs, discount, c, se); //Compute values for heston model
         double el_time = (clock() - st_time) / CLOCKS_PER_SEC;
         mc::DoOutput(c, se, el_time); //Output option value, standard error, and time taken for heston model
     }
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  else if statement executed if the user chooses gbm
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
     else if(model_type == "gbm") {

         ut::OutputLine("Standard GBM");
         double p; //Option value
         double discount = std::exp(-mc.r * mc.T); //Discount rate
         double se_2; //Option standard error
         double minimum; //minimum value of stock
         double maximum; //maximum value of stock
         std::vector<double> gbm_stock(mc.N, 0.0); //Vector to hold the standard GBM stock path

        for (long j = 1; j <= mc.M; ++j) {

            ut::OutputCounter(j, mc.M, 50000);
            double S = mc.S_0; //Initial stock value

            for(long i = 0; i <= mc.N-1; ++i)
             {
                 S = mc::Next_S(S, (mc.r - 0.5*mc.sig*mc.sig)*mc.T/mc.N, mc.sig*std::sqrt(mc.T/mc.N)); //Calculate stock path for standard GBM
                 gbm_stock[i] = S; //Insert stock value into standard GBM stock path
             }
             minimum = *std::min_element(gbm_stock.begin(), gbm_stock.end()); //Retrieve min stock value
             maximum = *std::max_element(gbm_stock.begin(), gbm_stock.end()); //Retrieve max stock value

             double payoff;
             if (option_type == "Call") {
                 payoff = pf::Call(S, mc.X);
             } else if (option_type == "Put") {
                 payoff = pf::Put(S, mc.X);
             } else if (option_type == "LookbackCallFixedStrike") {
                 payoff = pf::LookbackCallFixed(maximum, mc.X);
             } else if (option_type == "LookbackCallFloatingStrike") {
                 payoff = pf::LookbackCallFloat(S, minimum);
             } else if (option_type == "LookbackPutFixedStrike") {
                 payoff = pf::LookbackPutFixed(minimum, mc.X);
             } else if (option_type == "LookbackPutFloatingStrike") {
                 payoff = pf::LookbackPutFloat(S, maximum);
             }
             mc::Accumulate(payoff, acc_vals_2, acc_squs_2); //Accumulate payoffs and squared payoffs
         }

         //Do output for standard GBM
         mc::ComputeValues(mc, acc_vals_2, acc_squs_2, discount, p, se_2); //Compute values for standard GBM model
         std::cout << "\n";
        double el_time = (clock() - st_time) / CLOCKS_PER_SEC;
        mc::DoOutput(p, se_2, el_time); //Output option value, standard error, and time taken for the standard GBM model
     }


    return ut::PauseAndReturn();
        //return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

