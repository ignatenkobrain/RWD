#ifndef STOREINMEMORYOBSERVER_H
#define STOREINMEMORYOBSERVER_H
#include <vector>
#include <include/RWDFramework/ModelConfiguration.h>


namespace RWDFramework {

//typedef boost::numeric::ublas::vector<double> state_t;

namespace observers {

class StoreInMemoryObserver {

private:
    ObserverConfiguration * cfg;

public:

    std::vector<state_t> & states;
    std::vector<double> & times;

    StoreInMemoryObserver(ObserverConfiguration * observerConfig, std::vector<state_t> & statesVector,
                          std::vector<double> & timesVector) :
        cfg(observerConfig),
        states(statesVector),
        times(timesVector)
    {

    }

    void operator() (const RWDFramework::state_t & x, const double t) {
        if (cfg->trackTime) {
            times.push_back(t);
        }
        if (cfg->trackAll) {
            states.push_back(x);
        }
    }

};

}// namespace observers

}//namespace RWDFramework



#endif // STOREINMEMORYOBSERVER_H
