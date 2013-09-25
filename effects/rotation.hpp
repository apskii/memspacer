#ifndef EFFECTS_ROTATION_HPP
#define EFFECTS_ROTATION_HPP

#include "../core/defs.hpp"
#include "../core/effect.hpp"

TPL(Oriented) struct Rotation : public Effect<Oriented> {
    float duration;
    Quat orientation;
    Rotation(float duration, Quat orientation)
        : duration(duration)
        , orientation(orientation)
    {}
    virt is_expired() const -> bool {
        return duration <= 0;
    }
    virt apply(Oriented& obj, float delta) const -> void {
        obj.orientation = glm::mix(obj.orientation, orientation, delta / duration);
    }
    virt update(float delta) -> void {
        duration -= delta;
    }
};

TPL(Oriented) func rotation(float duration, Quat orientation, Pool* pool = implicit_effect_pool) -> WrapEffectTerm<Oriented> {
    return WrapEffectTerm<Oriented>(new (pool->malloc()) Rotation<Oriented>(duration, orientation));
}

#endif EFFECTS_ROTATION_HPP