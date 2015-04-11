#ifndef INTEGRATE_HPP
#define INTEGRATE_HPP
#include <stddef.h>
#include <eigen3/Eigen/Dense>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <include/RWDFramework/odeint_eigen_integration.hpp>
#include <include/RWDFramework/config.h>

namespace RWDFramework {

typedef boost::numeric::ublas::vector<double> state_t;

struct Methods {

    const static size_t RK_4 = 0;
    const static size_t RK_adaptive = 1;

};

template<typename System,typename Observer>
void integrate(System & system,state_t & startState,
               const double startTime,const double endTime,const size_t maxPoints, Observer & observer,
               size_t method = Methods::RK_4) {

    double minStep = (endTime-startTime)/maxPoints;
    //(observer)(startState,0.0);

    if(method == Methods::RK_4) {
        using namespace boost::numeric::odeint;
        runge_kutta4<state_t,double,state_t,double,vector_space_algebra> stepper;
        integrate_const(stepper,system,startState,startTime,endTime,minStep,observer);
    } else if (method == Methods::RK_adaptive) {
        using namespace boost::numeric::odeint;
        typedef runge_kutta_cash_karp54< state_t > error_stepper_type;
        typedef controlled_runge_kutta< error_stepper_type > controlled_stepper_type;
        controlled_stepper_type controlled_stepper;
        integrate_adaptive(controlled_stepper,system,startState,startTime,endTime,minStep,observer);
    }

}

} // namespace RWDFramework




#endif // INTEGRATE_HPP
