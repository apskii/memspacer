#pragma once

#include "../core/defs.hpp"
#include "../core/game_object.hpp"
#include "cell.hpp"

namespace game_objects {
    class Cube : public core::GameObjectTemplate<Cube> {
    typedef Cell<Cube> C;
    public:
        C cells[3][3][3];
        float cell_size;
        float cell_interval;
        Cube(Vec3 position = Vec3(0), Quat orientation = glm::angleAxis(0.f, 0.f, 0.f, 1.f))
            : core::GameObjectTemplate<Cube>(position, orientation)
            , cell_size(0.3)
            , cell_interval(0.1)
        {
            float dp = cell_size + cell_interval;
            position -= dp;
            for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                    for (int z = 0; z < 3; ++z)
                        cells[x][y][z] = C(
                          this,
                          Vec3 {
                            position.x + x * dp,
                            position.y + y * dp,
                            position.z + z * dp
                          },
                          glm::angleAxis(0.f, 0.f, 0.f, 1.f)
                        );
        }
        virtual void render(const core::RenderContext& ctx) {
            C* cells_ptr = &cells[0][0][0];
            ctx.default_shader.use();
            for (int i = 0; i < 27; ++i) {
                (cells_ptr + i)->render(ctx);
            }
        }
        virtual void update(float delta, Pool& pool) {
            GameObjectTemplate::update(delta, pool);
            C* cells_ptr = &cells[0][0][0];
            for (int i = 0; i < 27; ++i) {
                (cells_ptr + i)->update(delta, pool);
            }
        }
    };
}
