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

class ObserverWrapper {

private:
    RWDFramework::Observer & obs;

public:

    ObserverWrapper(RWDFramework::Observer & observer) : obs(observer) {
    }

    ~ObserverWrapper() {
    }

    void operator() (const RWDFramework::state_t & x, const double t) {
        obs(x,t);
    }

};



#endif // MODELWRAPPER_H
