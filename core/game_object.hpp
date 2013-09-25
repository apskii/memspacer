#ifndef CORE_GAME_OBJECT_HPP
#define CORE_GAME_OBJECT_HPP

#include <vector>
#include "defs.hpp"
#include "effect.hpp"

struct GameObject {
    Vec3 position;
    Quat orientation;
    GameObject(Vec3 position, Quat orientation)
        : position(position), orientation(orientation)
    {}
    virt update(float) -> void = 0;
    virt draw()        -> void = 0;    
};

TPL(Self) class GameObjectTemplate : public GameObject {
public:
    GameObjectTemplate(Vec3 position, Quat orientation)
        : GameObject(position, orientation)
    {}
    virt draw() -> void = 0;
    virt update(float delta) -> void {
        for (auto effect : effects) {
            effect->update(delta);
            if (!effect->is_expired())
                effect->apply(*((Self*) this));
        }
    }
    meth add_effect(Effect<Self> effect) -> void {
        effects.push_back(effect);
    }
private:
    std::vector<Effect<Self>*> effects;
};

#endif CORE_GAME_OBJECT_HPP