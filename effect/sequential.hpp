#ifndef CORE_EFFECT_SEQUENTIAL_HPP
#define CORE_EFFECT_SEQUENTIAL_HPP

#include "../core/defs.hpp"
#include "../core/effect.hpp"

namespace effect {
    using core::Effect;

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
        virt free(Pool& pool) -> void {
            pool.free(&first);
            pool.free(&second);
        }
        virt process(T& target, float delta) -> bool {
            if (!first_done) {
                if (first.process(target, delta))
                    first_done = true;
                return false;
            }
            else {
                return second.process(target, delta);
            }
        }
    };
}

#endif CORE_EFFECT_SEQUENTIAL_HPP