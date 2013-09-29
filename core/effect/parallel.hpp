#ifndef CORE_EFFECT_PARALLEL_HPP
#define CORE_EFFECT_PARALLEL_HPP

#include "../defs.hpp"
#include "../effect.hpp"

TPL(T) class Parallel : public Effect<T> {
private:
    Effect<T>& first;
    Effect<T>& second;
    bool first_done;
public:
    Parallel(Effect<T>& first, Effect<T>& second)
        : first(first)
        , second(second)
        , first_done(false)
    {}
    virt free(Pool& pool) -> void {
        pool.free(&first);
        pool.free(&second);
    }
    virt process(T& target, float delta) -> bool {
        if (!first_done) {
            if (first.process(target, delta))
                first_done = true;
        }
        return second.process(target, delta) && first_done;
    }
};

#endif CORE_EFFECT_PARALLEL_HPP