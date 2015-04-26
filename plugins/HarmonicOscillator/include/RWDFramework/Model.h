#ifndef INTEGRABLE_H
#define INTEGRABLE_H
#include <map>
#include <boost/numeric/odeint.hpp>
#include <iostream>


namespace RWDFramework {

typedef boost::numeric::ublas::vector<double> state_t;

class Integrable {

protected:
    std::map<std::string,double> params;

public:

    Integrable() {

    }

    virtual ~Integrable() {

    }

    virtual void operator() (const state_t & x, state_t & dxdt,const double t) = 0;

    std::map<std::string,double> & getParameters() {
        return params;
    }

    void setParameters(const std::map<std::string,double> & parameters) {
        this->params = parameters;
    }
};
} // namespace RWDFramework


#endif // INTEGRABLE_H
