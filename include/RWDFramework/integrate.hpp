#ifndef INTEGRATE_HPP
#define INTEGRATE_HPP
#include <stddef.h>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <include/RWDFramework/odeint_eigen_integration.hpp>
#include <include/RWDFramework/ModelConfiguration.h>

namespace RWDFramework {

typedef boost::numeric::ublas::vector<double> state_t;


//TODO: Remove unnecessary templates
template<typename System,typename Observer>
void integrate(System & system,state_t & startState,MethodConfiguration * methodConfig,Observer & observer) {

    std::string method = boost::algorithm::to_upper_copy(methodConfig->methodName);
    if(method == Methods::RK_4) {
        using namespace boost::numeric::odeint;
        runge_kutta4<state_t,double,state_t,double,vector_space_algebra> stepper;
        double step = (methodConfig->endTime - methodConfig->startTime)/(double) methodConfig->numberOfPoints;
        integrate_const(stepper,system,startState,methodConfig->startTime,methodConfig->endTime,step,observer);
    } else if (method == Methods::CASH_KARP) {
        using namespace boost::numeric::odeint;
        typedef runge_kutta_cash_karp54< state_t > error_stepper_type;

        //First parameter of controlled stepper is absolute tolerance error, second is relative tolerance error
        //Method step value is hardcoded to 0.01, may be later I change it
        integrate_adaptive(make_controlled<error_stepper_type>(methodConfig->absError,methodConfig->relError),
                           system,startState,methodConfig->startTime,methodConfig->endTime,
                           0.01 /*Cause method with adaptive size*/,observer);
    }

}

} // namespace RWDFramework




#endif // INTEGRATE_HPP
