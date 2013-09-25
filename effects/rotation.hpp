#ifndef EFFECTS_ROTATION_HPP
#define EFFECTS_ROTATION_HPP

#include "../core/defs.hpp"
#include "../core/effect.hpp"

TPL(Rotatable) struct Rotation : public Effect<Rotatable> {
    Quat orientation;
    Rotation(Quat orientation)
        : orientation(orientation)
    {}
    virt is_expired() const -> bool {
        return true;
    }
    virt apply(Rotatable& obj) const -> void {

    }
    virt update(float) -> void {
    }
};

#endif EFFECTS_ROTATION_HPP