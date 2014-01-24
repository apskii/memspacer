#pragma once

#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "../effect/algebra.hpp"

namespace effects {
    TPL(Colored) struct Blink : public core::Effect<Colored> {
        float duration;
        // float remaining;
        const Vec4 color;
        Blink(float duration, Vec4 color)
            : duration(duration)
            , color(color)
        {}
        virtual bool process(Colored& target, float delta) {
            target.color += (color - target.color) * delta / duration;
            if ((duration -= delta) <= 0) {
                target.color = color;
                return true;
            }
            return false;
        }
    };

    namespace {
        struct DummyColored { Vec4 color; };
        CHECK_EFFECT(Blink, Blink<DummyColored>);
    }

    TPL(Colored) effect::WrapEffectTerm<Colored> blink(float duration, Vec4 color, Pool& pool) {
        return effect::WrapEffectTerm<Colored>(new (pool.malloc()) Blink<Colored>(duration, color));
    }
}
