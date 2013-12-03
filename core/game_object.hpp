#pragma once

#include <list>
#include "defs.hpp"
#include "effect.hpp"

namespace core {
    struct GameObject {
        Vec3 position;
        Quat orientation;
        GameObject() {}
        GameObject(Vec3 position, Quat orientation)
            : position(position), orientation(orientation)
        {}
        virtual void update(float, Pool&)         = 0;
        virtual void render(const RenderContext&) = 0;
    };

    TPL(Self) class GameObjectTemplate : public GameObject {
    public:
        GameObjectTemplate() {}
        GameObjectTemplate(Vec3 position, Quat orientation)
            : GameObject(position, orientation)
        {}
        virtual void render(const RenderContext&) = 0;
        virtual void update(float delta, Pool& pool) {
            auto it = std::begin(effects);
            auto end = std::end(effects);
            while (it != end) {
                auto effect = *it;
                if (!effect->process(*((Self*) this), delta)) {
                    ++it;
                }
                else {
                    it = effects.erase(it);
                    effect->free(pool);
                    pool.free(effect);
                }
            }
        }
        void attach_effect(Effect<Self>* effect) {
            effects.push_back(effect);
        }
    private:
        std::list<Effect<Self>*> effects;
    };
}
