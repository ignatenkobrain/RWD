#include <include/models/create_model.h>
#include <include/models/osc-model.h>

extern "C" Integrable * createIntegrable() {
    Integrable * osc = new harm_osc;
    return osc;

}



