#pragma once

#include <type_traits>
#include "defs.hpp"

namespace core {
    TPL(T) struct Effect {
        // virtual void free(Pool&);
        virtual bool process(T&, float) = 0;
    };

    TPL(E) struct CheckEffect {
        static_assert(sizeof(E) <= 40,
            "Effect subclasses should have sizeof <= 32 to fit into object pools."
        );
    };
}

#define CHECK_EFFECT(NAME, TYPE) struct NAME ## Checker : public core::CheckEffect<TYPE> {}
