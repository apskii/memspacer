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
    virt init(const Oriented& target) -> void {
        orientation = orientation * target.orientation;
    }
    virt update(const Oriented&, float delta) -> void {
        duration -= delta;
    }
    virt is_expired() const -> bool {
        return duration <= 0;
    }
    virt apply(Oriented& target, float delta) const -> void {
        target.orientation = glm::mix(target.orientation, orientation, std::min(delta / duration, 1.f));
    }
};

struct Cube;
CHECK_EFFECT(Rotation, Rotation<Cube>);

TPL(Oriented) func rotation(float duration, Quat orientation, Pool& pool) -> WrapEffectTerm<Oriented> {
    return WrapEffectTerm<Oriented>(new (pool.malloc()) Rotation<Oriented>(duration, orientation));
}

#endif EFFECTS_ROTATION_HPP