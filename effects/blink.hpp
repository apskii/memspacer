#ifndef EFFECTS_BLINK_HPP
#define EFFECTS_BLINK_HPP

#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "../core/effect/algebra.hpp"

TPL(Colored) struct Blink : public Effect<Colored> {
    float duration;
    const Vec4 color;
    Blink(float duration, Vec4 color)
        : duration(duration)
        , color(color)
    {}
    virt is_expired() const -> bool {
        return duration <= 0;
    }
    virt apply(Colored& obj, float delta) const -> void {
        obj.color += (color - obj.color) * delta / duration;
    }
    virt update(float delta) -> void {
        duration -= delta;
    }
};

CHECK_EFFECT(Blink, Blink<Cell>);

TPL(Colored) func blink(float duration, Vec4 color, Pool& pool) -> WrapEffectTerm<Colored> {
    return WrapEffectTerm<Colored>(new (pool.malloc()) Blink<Colored>(duration, color));
}

#endif EFFECTS_BLINK_HPP