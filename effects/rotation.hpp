#pragma once

#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "../effect/algebra.hpp"

namespace effects {
    TPL(Oriented) struct Rotation : public core::Effect<Oriented> {
        const float duration;
        float remaining;
        float delta_sum;
        Quat orientation;
        Rotation(float duration, Quat orientation)
            : duration(duration)
            , remaining(duration)
            , orientation(orientation)
            , delta_sum(0.f)
        {}
        virtual bool process(Oriented& target, float delta) {
            static const auto unit = Quat();
            auto delta_step = delta / duration;
            delta_sum += delta_step;
            if (delta_sum > 1.f)
                delta_step = delta_step - delta_sum + 1.f;
            auto delta_o = glm::mix(unit, orientation, delta_step);
            target.orientation = delta_o * target.orientation;
            return (remaining -= delta) <= 0;
        }
    };

    namespace {
        struct DummyOriented { Quat orientation; };
        CHECK_EFFECT(Rotation, Rotation<DummyOriented>);
    }

    TPL(Oriented) effect::WrapEffectTerm<Oriented> rotation(float duration, Quat orientation, Pool& pool) {
        return effect::WrapEffectTerm<Oriented>(new (pool.malloc()) Rotation<Oriented>(duration, orientation));
    }
}
