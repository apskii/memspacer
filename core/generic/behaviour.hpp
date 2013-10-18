#ifndef CORE_GENERIC_BEHAVIOUR
#define CORE_GENERIC_BEHAVIOUR

#include "../defs.hpp"

TPL(Context) struct Behaviour {
    virt process(Context&, float) -> bool;
};

#endif CORE_GENERIC_BEHAVIOUR