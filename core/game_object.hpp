#ifndef CORE_GAME_OBJECT_HPP
#define CORE_GAME_OBJECT_HPP

#include <list>
#include "defs.hpp"
#include "effect.hpp"

namespace core {
    TPL(RenderContext) struct GameObject {
        Vec3 position;
        Quat orientation;
        GameObject() {}
        GameObject(Vec3 position, Quat orientation)
            : position(position), orientation(orientation)
        {}
        virt update(float, Pool&)         -> void = 0;
        virt render(const RenderContext&) -> void = 0;
    };

    TPL_2(Self, RenderContext) class GameObjectTemplate : public GameObject<RenderContext> {
    public:
        GameObjectTemplate() {}
        GameObjectTemplate(Vec3 position, Quat orientation)
            : GameObject(position, orientation)
        {}
        virt render(const RenderContext&) -> void = 0;
        virt update(float delta, Pool& pool) -> void {
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
        meth attach_effect(Effect<Self>* effect) -> void {
            effects.push_back(effect);
        }
    private:
        std::list<Effect<Self>*> effects;
    };
}

#endif CORE_GAME_OBJECT_HPP