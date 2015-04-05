#ifndef OSCMODEL_H
#define OSCMODEL_H
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>
#include "include/RWDFramework/integrable.h"

//typedef Eigen::VectorXd state_t;
using state_t = Eigen::Matrix<double, 2, 1>;
//typedef std::vector<double> state_t;

class harm_osc : Integrable {

public:

    void operator() (const state_t &x , state_t &dxdt,const double t)
    {
        dxdt[0] = x[1];
        dxdt[1] = -4.*x[0];
    }
};

class harm_osc_observer {

public:
    void operator()(const state_t &x, const double t) {
        // time | numeric solution | symbolic solution
        std::cout<<t<<" "<<x[0]<<" "<<0.2*cos(2.*t)<<std::endl;
    }

};


#endif // OSCMODEL_H
