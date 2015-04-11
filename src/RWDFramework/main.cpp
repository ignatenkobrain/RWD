#include <include/RWDFramework/integrate.hpp>
#include <include/RWDFramework/Model.h>
#include <include/RWDFramework/ModelFactory.hpp>
#include <include/RWDFramework/ModelWrapper.h>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {

    std::string libName(argv[1]);
    std::cout<<libName;
    RWDFramework::ModelFactory factory;
    RWDFramework::Integrable * osc = factory.getModel(libName);
    RWDFramework::Observer * observer = factory.getObserver(libName);
    RWDFramework::state_t start_state(2);
    start_state[0] = 0.2;
    start_state[1] = 0.;
    IntegrableWrapper wrapper(*osc);
    ObserverWrapper obs(*observer);

    RWDFramework::integrate(wrapper,start_state,0.,5.,20,obs,RWDFramework::Methods::RK_4);
    delete osc;
    delete observer;
}
