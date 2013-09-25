#ifndef EFFECTS_BLINK_HPP
#define EFFECTS_BLINK_HPP

#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "../core/effect/algebra.hpp"
// #include "algebra.hpp"
#include "../game_objects/cell.hpp"

struct Blink : public Effect<Cell> {
    float duration;
    const Vec4 color;
    Blink(float duration, Vec4 color)
        : duration(duration)
        , color(color)
    {}
    virt is_expired() const -> bool { return true; }
    virt apply(Cell&) const -> void {
    }
    virt update(float) -> void {}
};

CHECK_EFFECT(Blink);

func blink(float duration, Vec4 color, Pool& pool) -> WrapEffectTerm<Cell> {
    return WrapEffectTerm<Cell>(new (pool.malloc()) Blink(duration, color));
}

#endif EFFECTS_BLINK_HPP