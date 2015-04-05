#ifndef INTEGRABLE_H
#define INTEGRABLE_H
#include <vector>
#include <eigen3/Eigen/Dense>

using state_t = Eigen::Matrix<double, 2, 1>;

class Integrable {

public:

    void operator() (const state_t & x, state_t & dxdt,const double t);


};

#endif // INTEGRABLE_H
