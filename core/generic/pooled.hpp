#ifndef CORE_GENERIC_POOLED
#define CORE_GENERIC_POOLED

#include "../defs.hpp"

struct Pooled {
    virt free(Pool&) -> void;
};

#endif CORE_GENERIC_POOLED