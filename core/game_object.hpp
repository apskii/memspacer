#ifndef CORE_GAME_OBJECT_HPP
#define CORE_GAME_OBJECT_HPP

#include <list>
#include "defs.hpp"
#include "effect.hpp"

struct GameObject {
    Vec3 position;
    Quat orientation;
    GameObject(Vec3 position, Quat orientation)
        : position(position), orientation(orientation)
    {}
    virt update(float, Pool&) -> void = 0;
    virt draw()               -> void = 0;
    meth update_position(Vec3 position) -> void {
        this->position = position;
    }
    meth update_orientation(Quat orientation) -> void {
        this->orientation = orientation;
    }
};

TPL(Self) class GameObjectTemplate : public GameObject {
public:
    GameObjectTemplate(Vec3 position, Quat orientation)
        : GameObject(position, orientation)
    {}
    virt draw() -> void = 0;
    virt update(float delta, Pool& pool) -> void {
        auto it = std::begin(effects);
        auto end = std::end(effects);
        while (it != end) {
            auto effect = *it;
            effect->update(delta);
            if (!effect->is_expired()) {
                effect->apply(*((Self*) this), delta);
                ++it;
            } else {
                it = effects.erase(it);
                pool.free(effect);
            }
        }
    }
    meth add_effect(Effect<Self>* effect) -> void {
        effects.push_back(effect);
    }
private:
    std::list<Effect<Self>*> effects;
};

#endif CORE_GAME_OBJECT_HPP