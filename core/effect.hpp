#ifndef CORE_EFFECT_HPP
#define CORE_EFFECT_HPP

#include <type_traits>
#include "defs.hpp"

struct GameObject;

static Pool* implicit_effect_pool;

TPL(T) struct Effect {    
    static_assert(std::is_base_of<GameObject, T>::value,
        "T <: GameObject required in Effect<T>."
    );    
    virt is_expired()     const -> bool = 0;
    virt apply(T&, float) const -> void = 0;
    virt update(float)          -> void = 0;
};

TPL(E) class CheckEffect {
    static_assert(sizeof(E) <= 32,
        "Effect subclasses should have sizeof <= 32 to fit into object pulls."
    );
};

#define CHECK_EFFECT(NAME, TYPE) struct NAME ## Checker : public CheckEffect<TYPE> {}

#endif CORE_EFFECT_HPP