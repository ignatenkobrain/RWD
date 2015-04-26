#ifndef OSCMODEL_H
#define OSCMODEL_H
#include <iostream>
#include <include/RWDFramework/Model.h>

using namespace RWDFramework;

class harm_osc : public Integrable {

public:

    ~harm_osc() {
    }

    harm_osc() {
    }

    void operator() (const state_t &x , state_t &dxdt,const double t)
    {
        dxdt[0] = x[1];
        dxdt[1] = -params["w_0"]*x[0];
    }
};



#endif // OSCMODEL_H
