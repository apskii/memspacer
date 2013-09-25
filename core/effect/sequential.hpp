#ifndef CORE_EFFECT_SEQUENTIAL_HPP
#define CORE_EFFECT_SEQUENTIAL_HPP

#include "../defs.hpp"
#include "../effect.hpp"

TPL(T) class Sequential : public Effect<T> {    
private:
    Effect<T>* first;
    Effect<T>* second;
public:
    Sequential(Effect<T>* first, Effect<T>* second)
        : first(first)
        , second(second)
    {}
    virt is_expired() const -> bool {
        return second->is_expired();
    }
    virt apply(T& target) const -> void {
        if (first->is_expired())
            second->apply(target);
        else
            first->apply(target);
    }
    virt update(float delta) -> void {
        if (first->is_expired())
            second->update(delta);
        else
            first->update(delta);
    }
};

#endif CORE_EFFECT_SEQUENTIAL_HPP