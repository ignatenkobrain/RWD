#ifndef INTEGRABLEFACTORY_H
#define INTEGRABLEFACTORY_H
#include <string>
#include <include/RWDFramework/Model.h>
#include <dlfcn.h>

namespace RWDFramework {
class ModelFactory {

private:
    template<typename Object>
    Object * getObject(const std::string &pathToObjectLib, const std::string & interfaceName) {
        void *handle;
        Object * (*getObj)();
        char *error;
        handle = dlopen (pathToObjectLib.c_str(), RTLD_LAZY );
        if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        std::string factoryName = "create";
        factoryName.append(interfaceName);
        getObj = (Object * (*)())dlsym(handle, factoryName.c_str());
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }
        Object * obj = getObj();
        dlclose(handle);
        return obj;
    }

public:

    Integrable * getModel(const std::string & pathToModelLib) {
        return getObject<Integrable>(pathToModelLib,"Integrable");
    }

    Observer * getObserver(const std::string &pathToObserverLib) {
        return getObject<Observer>(pathToObserverLib,"Observer");
    }


};
} // namespace RWDFramework



#endif // INTEGRABLEFACTORY_H
