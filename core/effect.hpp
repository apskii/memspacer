#ifndef CORE_EFFECT_HPP
#define CORE_EFFECT_HPP

#include <type_traits>
#include "defs.hpp"
#include "generic/behaviour.hpp"
#include "generic/pooled.hpp"

TPL(T) struct Effect : Pooled, Behaviour<T> {};

TPL(E) struct CheckEffect {
    static_assert(sizeof(E) <= 32,
        "Effect subclasses should have sizeof <= 32 to fit into object pools."
    );
};

#define CHECK_EFFECT(NAME, TYPE) struct NAME ## Checker : public CheckEffect<TYPE> {}

#endif CORE_EFFECT_HPP