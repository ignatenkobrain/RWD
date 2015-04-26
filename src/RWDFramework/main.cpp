#include <include/RWDFramework/integrate.hpp>
#include <include/RWDFramework/Model.h>
#include <include/RWDFramework/ModelFactory.hpp>
#include <include/RWDFramework/ModelWrapper.h>
#include <eigen3/Eigen/Dense>
#include <include/RWDFramework/observers/StoreInMemoryObserver.h>
#include <vector>
#include <iostream>
#include <QtXml/qdom.h>

int main(int argc, char *argv[]) {

    std::string lib = argv[1];
    auto * cfgReader = new RWDFramework::ConfigReader;
    RWDFramework::ModelConfiguration * modelCfg;
    RWDFramework::MethodConfiguration * methodCfg;
    RWDFramework::ObserverConfiguration * observerCfg;
    std::cout<<"Reading config file"<<std::endl;
    if (cfgReader->readConfigFromFile(lib)) {
        modelCfg = cfgReader->getModelConfiguration();
        methodCfg = cfgReader->getMethodConfiguration();
        observerCfg = cfgReader->getObserverConfiguration();
    } else {
        std::cerr<<"Parsing error"<<std::endl;
    }
    RWDFramework::ModelFactory factory;
    RWDFramework::Integrable * osc = factory.getModel(modelCfg->pathToPlugin);
    osc->setParameters(modelCfg->parameters);

    IntegrableWrapper wrapper(*osc);

    if (observerCfg->type == "memory_storing") {
        std::vector<double> times;
        std::vector<RWDFramework::state_t> states;
        boost::numeric::ublas::vector<double> s(2);
        s[0]= 0.2;
        s[1] = 0.;
        RWDFramework::observers::StoreInMemoryObserver observer(observerCfg,states,times);
        RWDFramework::integrate(wrapper,s,methodCfg,observer);
        for(size_t i = 0;i < times.size();i++) {
            std::cout<<times[i]<<" "<<states.at(i)[0]<<" "<<0.2*cos(2.*times[i])<<std::endl;
        }
    }

}
