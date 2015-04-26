#ifndef INTEGRABLEFACTORY_H
#define INTEGRABLEFACTORY_H
#include <string>
#include <include/RWDFramework/Model.h>
#include <dlfcn.h>

namespace RWDFramework {
class ModelFactory {

private:

    //
    // TODO: Additional interface for system of 2nd order ODE will be added later.
    //
    template<typename Object>
    Object * getObject(const std::string &pathToObjectLib, const std::string & interfaceName) {
        void *handle;
        Object * (*getObj)();
        char *error;
        handle = dlopen (pathToObjectLib.c_str(), RTLD_LAZY );
        if (!handle) {
            fputs (dlerror(), stderr);
            fputs("\n", stderr);
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

};
} // namespace RWDFramework



#endif // INTEGRABLEFACTORY_H
