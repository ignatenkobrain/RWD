#include <include/RWDFramework/integrate.hpp>
#include <include/models/osc-model.h>
#include <eigen3/Eigen/Dense>
#include <vector>


int main(int argc, char ** argv) {

    harm_osc osc;
    harm_osc_observer observer;
    state_t start_state(2);
    start_state<<0.2, 0.;
    RWDFramework::integrate(osc,start_state,0.,5.,20,observer,RWDFramework::Methods::RK_adaptive);

}
