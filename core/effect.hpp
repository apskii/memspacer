#ifndef CORE_EFFECT_HPP
#define CORE_EFFECT_HPP

#include <type_traits>
#include "defs.hpp"

TPL(T) struct Effect {
    virt free(Pool&)        -> void  {};
    virt process(T&, float) -> bool = 0;
};

TPL(E) class CheckEffect {
    static_assert(sizeof(E) <= 32,
        "Effect subclasses should have sizeof <= 32 to fit into object pools."
    );
};

#define CHECK_EFFECT(NAME, TYPE) struct NAME ## Checker : public CheckEffect<TYPE> {}

#endif CORE_EFFECT_HPP