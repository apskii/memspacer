#ifndef CORE_EFFECT_HPP
#define CORE_EFFECT_HPP

#include <type_traits>
#include "defs.hpp"

namespace core {
    TPL(T) struct Effect {
        virt free(Pool&) -> void;
        virt process(T&, float) -> bool;
    };

    TPL(E) struct CheckEffect {
        static_assert(sizeof(E) <= 32,
            "Effect subclasses should have sizeof <= 32 to fit into object pools."
        );
    };
}

#define CHECK_EFFECT(NAME, TYPE) struct NAME ## Checker : public core::CheckEffect<TYPE> {}

#endif CORE_EFFECT_HPP