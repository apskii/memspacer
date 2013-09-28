#ifndef GAME_OBJECTS_CUBE_HPP
#define GAME_OBJECTS_CUBE_HPP

#include "../core/defs.hpp"
#include "../core/game_object.hpp"
// #include "../effects/blink.hpp"
// #include "../effects/rotation.hpp"
#include "cell.hpp"

class Cube : public GameObjectTemplate<Cube> {
private:
    Cell<Cube> cells[3][3][3];
public:
    float cell_size;
    float cell_interval;
    Cube(Vec3 position = Vec3(), Quat orientation = glm::angleAxis(0.f, 0.f, 0.f, 1.f))
        : GameObjectTemplate(position, orientation)
        , cell_size(0.3)
        , cell_interval(0.05)
    {
        float dp = cell_size + cell_interval;
        position -= dp;
        for (int x = 0; x < 3; ++x)
            for (int y = 0; y < 3; ++y)
                for (int z = 0; z < 3; ++z)
                    cells[x][y][z] = Cell<Cube>(
                        this,
                        Vec3 {
                            position.x + x * dp,
                            position.y + y * dp,
                            position.z + z * dp
                        },
                        glm::angleAxis(0.f, 0.f, 0.f, 1.f)
                    );
    }
    virt draw() -> void {
        Cell<Cube>* cells_ptr = &cells[0][0][0];
        for (int i = 0; i < 27; ++i) {
            (cells_ptr + i)->draw();
        }
    }
    virt update(float delta, Pool& pool) -> void {
        GameObjectTemplate::update(delta, pool);
        Cell<Cube>* cells_ptr = &cells[0][0][0];
        for (int i = 0; i < 27; ++i) {
            (cells_ptr + i)->update(delta, pool);
        }
    }
};

#endif GAME_OBJECTS_CUBE_HPP