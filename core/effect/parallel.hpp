#ifndef CORE_EFFECT_PARALLEL_HPP
#define CORE_EFFECT_PARALLEL_HPP

#include "../defs.hpp"
#include "../effect.hpp"

TPL(T) class Parallel : public Effect<T> {
private:
    Effect<T>& first;
    Effect<T>& second;
public:
    Parallel(Effect<T>& first, Effect<T>& second)
        : first(first)
        , second(second)
    {}
    virt init(const T& target) -> void {
        first.init(target);
        second.init(target);
    }
    virt free(Pool& pool) -> void {
        pool.free(&first);
        pool.free(&second);
    }
    virt update(const T& target, float delta) -> void {
        first.update(target, delta);
        second.update(target, delta);
    }
    virt is_expired() const -> bool {
        return first.is_expired()
            && second.is_expired();
    }
    virt apply(T& target, float delta) const -> void {
        if (!first.is_expired())
            first.apply(target, delta);
        if (!second.is_expired())
            second.apply(target, delta);
    }
};

#endif CORE_EFFECT_PARALLEL_HPP