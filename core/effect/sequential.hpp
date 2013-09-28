#ifndef CORE_EFFECT_SEQUENTIAL_HPP
#define CORE_EFFECT_SEQUENTIAL_HPP

#include "../defs.hpp"
#include "../effect.hpp"

#include <iostream>

TPL(T) class Sequential : public Effect<T> {
private:
    Effect<T>& first;
    Effect<T>& second;
    bool first_done;
public:
    Sequential(Effect<T>& first, Effect<T>& second)
        : first(first)
        , second(second)
        , first_done(false)
    {}
    virt init(const T& target) -> void {
        first.init(target);
    }
    virt free(Pool& pool) -> void {
        pool.free(&first);
        pool.free(&second);
    }
    virt update(const T& target, float delta) -> void {
        if (!first_done) {
            first.update(target, delta);
            if (first.is_expired()) {
                first_done = true;
                second.init(target);
            }
        }
        else {
            second.update(target, delta);
        }
    }
    virt is_expired() const -> bool {
        return second.is_expired();
    }
    virt apply(T& target, float delta) const -> void {
        if (first_done) {
            second.apply(target, delta);
        }
        else {
            first.apply(target, delta);
        }
    }
};

#endif CORE_EFFECT_SEQUENTIAL_HPP