#ifndef MODELCONFIGURATION_H
#define MODELCONFIGURATION_H
#include <string>
#include <map>
#include <QtXml/qdom.h>
#include <boost/optional.hpp>
#include <boost/dynamic_bitset.hpp>
#include <include/RWDFramework/Model.h>

namespace RWDFramework {

struct Methods {

    static const std::string RK_4;
    static const std::string CASH_KARP;

};

struct ModelConfiguration {

    std::string modelName;

    std::string pathToPlugin;

    std::map<std::string, double> parameters;

    state_t startState;

};

struct MethodConfiguration {

    std::string methodName;

    size_t numberOfPoints;

    double absError;

    double relError;

    double startTime;

    double endTime;

    double step;

};

struct ObserverConfiguration {

    std::string type;

    std::string outputFileName;

    bool trackTime;

    bool trackAll;

    std::vector<size_t> trackingVars;

};

class ConfigReader {

private:
    ModelConfiguration *modelCfg;
    MethodConfiguration *methodCfg;
    ObserverConfiguration *observerCfg;
    boost::optional<QString> getElementValue(QDomElement & parent,const QString & childElementName);
    bool parseParametersConfig(QDomElement & modelElement);
    bool parseMethodConfig(QDomElement & modelElement);
    bool parseObserverConfig(QDomElement & modelElement);
    bool parseStartState(QDomElement & modelElement);

public:
    ConfigReader();
    ~ConfigReader();

    bool readConfigFromFile(const std::string & fileName);

    ModelConfiguration * getModelConfiguration();

    MethodConfiguration * getMethodConfiguration();

    ObserverConfiguration *getObserverConfiguration();

};

} // namespace RWDFramework





#endif // MODELCONFIGURATION_H
