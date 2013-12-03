#pragma once

#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "../effect/algebra.hpp"

/*
namespace effects {
    TPL(Colored) struct Blink : public core::Effect<Colored> {
        float duration;
        const Vec4 color;
        Blink(float duration, Vec4 color)
            : duration(duration)
            , color(color)
        {}
        virtual void update(const Colored&, float delta) {
            duration -= delta;
        }
        virt is_expired() const -> bool {
            return duration <= 0;
        }
        virtual void apply(Colored& obj, float delta) const {
            obj.color = (color - obj.color) * delta / duration;
        }
    };

    namespace {
        struct DummyColored { Vec4 color; };
        CHECK_EFFECT(Blink, Blink<DummyColored>);
    }

    TPL(Colored) func blink(float duration, Vec4 color, Pool& pool) -> effect::WrapEffectTerm<Colored> {
        return effect::WrapEffectTerm<Colored>(new (pool.malloc()) Blink<Colored>(duration, color));
    }
}*/
