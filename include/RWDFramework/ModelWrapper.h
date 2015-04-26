#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#include <include/RWDFramework/Model.h>
#include <iostream>

class IntegrableWrapper {

private:
    RWDFramework::Integrable & integrable;

public:

    IntegrableWrapper(RWDFramework::Integrable & model) : integrable(model) {
    }

    ~IntegrableWrapper() {

    }

    void operator() (const RWDFramework::state_t & x, RWDFramework::state_t &dxdt, const double t) {
        integrable(x,dxdt,t);
    }


};

#endif // MODELWRAPPER_H
