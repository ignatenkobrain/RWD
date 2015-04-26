#include <include/RWDFramework/ModelConfiguration.h>
#include <QFile>
#include <iostream>

//TODO: Think about refactoring

namespace RWDFramework {

const std::string Methods::RK_4 = "RK_4";
const std::string Methods::CASH_KARP = "CASH_KARP";

bool ConfigReader::readConfigFromFile(const std::string &fileName) {

    QFile * cfgFile = new QFile(fileName.c_str());
    if (!cfgFile->exists()) {
        std::cerr<<"Configuration file not found"<<std::endl;
        return false;
    }
    if (!cfgFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr<<"Unable to open parameters file"<<std::endl;
        return false;
    }
    QDomDocument * document = new QDomDocument;
    if(!document->setContent(cfgFile)) {
        //TODO: implement output of full error information
        std::cerr<<"Unable to parse config file"<<std::endl;
        return false;
    }
    QDomElement modelElement = document->documentElement();
    if (modelElement.tagName() != "model") {
        std::cerr<<"Can't find element 'model'"<<std::endl;
        return false;
    }
    if (modelElement.hasAttribute("name") && modelElement.hasAttribute("lib")) {
        modelCfg->modelName = modelElement.attribute("name").toStdString();
        modelCfg->pathToPlugin = modelElement.attribute("lib").toStdString();
    } else {
        std::cerr<<"Name or lib attribute of model element not found";
        return false;
    }

    if (parseParametersConfig(modelElement)
            && parseStartState(modelElement)
            && parseMethodConfig(modelElement)
            && parseObserverConfig(modelElement)) {
        return true;
    }
    return false;
}

//Return double if element found;
//else return non initialized variable
boost::optional<QString> ConfigReader::getElementValue(QDomElement & parent, const QString & childElementName) {

    QDomElement element = parent.namedItem(childElementName).toElement();
    if (element.isNull()) {
        return boost::optional<QString>();
    }
    return boost::optional<QString>(element.text());
}

bool ConfigReader::parseParametersConfig(QDomElement & modelElement) {

    QDomElement parametersElement = modelElement.namedItem("parameters").toElement();
    if (parametersElement.isNull()) {
        std::cerr<<"Can't find element 'parameters'"<<std::endl;
        return false;
    }
    QDomNodeList allParameters = parametersElement.childNodes();
    for (int i = 0;i < allParameters.size(); i++) {

        QDomElement paramElement = allParameters.at(i).toElement();
        std::string paramName = paramElement.nodeName().toStdString();
        //TODO: Check conversion from QString to double
        double paramValue = paramElement.text().toDouble();
        modelCfg->parameters[paramName] = paramValue;
    }
    return true;
}

bool ConfigReader::parseStartState(QDomElement &modelElement) {
    QDomElement startStateElement = modelElement.namedItem("startState").toElement();
    if (startStateElement.isNull()) {
        std::cerr<<"Can't find element 'startState'"<<std::endl;
        return false;
    }
    QDomNodeList state = startStateElement.childNodes();
    modelCfg->startState.resize(state.size());
    for (int i = 0;i < state.size(); i++) {
        QDomElement startValueElement = state.at(i).toElement();
        double startValue = startValueElement.text().toDouble();
        modelCfg->startState[i] = startValue;
    }
    return true;
}

bool ConfigReader::parseMethodConfig(QDomElement & modelElement) {

    QDomElement methodElement = modelElement.namedItem("method").toElement();
    if (methodElement.isNull()) {
        std::cerr<<"Can't find element 'method'"<<std::endl;
        return false;
    }
    boost::optional<QString> methodName = getElementValue(methodElement,"name");
    if (methodName) {
        methodCfg->methodName = methodName.get().toStdString();
    }
    boost::optional<QString> numberOfPoints = getElementValue(methodElement,"numberOfPoints");
    if (numberOfPoints) {
        methodCfg->numberOfPoints = numberOfPoints.get().toInt();
    }
    boost::optional<QString> absError = getElementValue(methodElement,"absError");
    if (absError) {
        methodCfg->absError = absError.get().toDouble();
    }
    boost::optional<QString> relError = getElementValue(methodElement,"relError");
    if (relError) {
        methodCfg->relError = relError.get().toDouble();
    }
    boost::optional<QString> startTime = getElementValue(methodElement,"startTime");
    if (startTime) {
        methodCfg->startTime = startTime.get().toDouble();
    } else {
        std::cerr<<"Start time isn't specitifed"<<std::endl;
        return false;
    }
    boost::optional<QString> endTime = getElementValue(methodElement,"endTime");
    if (endTime) {
        methodCfg->endTime = endTime.get().toDouble();
    } else {
        std::cerr<<"End time isn't specified"<<std::endl;
        return false;
    }

    return true;
}

bool ConfigReader::parseObserverConfig(QDomElement & modelElement) {

    //Full functionality of observer config parsing will be implemented later

    QDomElement observerElement = modelElement.namedItem("observer").toElement();
    if (observerElement.isNull()) {
        std::cerr<<"Element 'observer' not found"<<std::endl;
        return false;
    }
    if (observerElement.hasAttribute("type")) {
        observerCfg->type = observerElement.attribute("type").toStdString();
    } else {
        std::cout<<"Observer type isn't specified, memory storing observer will be used"<<std::endl;
        observerCfg->type = "memory_storing";
    }
    boost::optional<QString> trackTime = getElementValue(observerElement,"trackTime");
    if (trackTime) {
        //TODO: Make not case sensitive;
        //add additional false check to prevent misconfig;
        observerCfg->trackTime = (trackTime.get().toStdString() == "true") ? true : false;
    } else {
        observerCfg->trackTime = false;
    }
    boost::optional<QString> trackingVars = getElementValue(observerElement,"trackingVars");
    if (trackingVars) {
        QString trackingVarsString = trackingVars.get();
        //TODO: Make not case sensitive;
        //add missed logic of parsing string like 1-5,7,8 for select tracking variables numbers
        if (trackingVarsString == "all") {
            observerCfg->trackAll = true;
        }
    }
    return true;

}

ConfigReader::ConfigReader() : modelCfg(new ModelConfiguration),
                               methodCfg(new MethodConfiguration),
                               observerCfg(new ObserverConfiguration) {

}

ConfigReader::~ConfigReader() {

    delete modelCfg;
    delete methodCfg;
    delete observerCfg;
}

ModelConfiguration * ConfigReader::getModelConfiguration() {
    return modelCfg;
}

MethodConfiguration * ConfigReader::getMethodConfiguration() {
    return methodCfg;
}

ObserverConfiguration * ConfigReader::getObserverConfiguration() {
    return observerCfg;
}


} // namespasce RWDFramework


