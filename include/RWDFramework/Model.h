#ifndef INTEGRABLE_H
#define INTEGRABLE_H
#include <vector>
#include <eigen3/Eigen/Dense>
#include <boost/numeric/odeint.hpp>
#include <iostream>


namespace RWDFramework {

typedef boost::numeric::ublas::vector<double> state_t;

class Integrable {

private:

    std::vector<double> parameters;

public:

    Integrable(const std::vector<double> & parameters){
        this->parameters = parameters;
    }

    Integrable() {

    }

    virtual ~Integrable() {

    }

    virtual void operator() (const state_t & x, state_t & dxdt,const double t) = 0;

    std::vector<double> & getParameters() {
        return parameters;
    }

    void setParameters(const std::vector<double> & parameters) {
        this->parameters = parameters;
    }


};

class Observer {

public:

   Observer() {

   }

   virtual ~Observer() {

   }

   virtual void operator() (const state_t & x,const double t) = 0;


};

} // namespace RWDFramework


#endif // INTEGRABLE_H
