#ifndef GAME_OBJECTS_CUBE_HPP
#define GAME_OBJECTS_CUBE_HPP

#include "../core/game_object.hpp"
#include "cell.hpp"
#include "../effects/blink.hpp"
#include "../effects/rotation.hpp"

class Cube : public GameObjectTemplate<Cube> {
private:
    Cell cells[3][3][3];
public:
    static float cell_interval;
    Cube(Vec3 position, Quat orientation)
        : GameObjectTemplate(position, orientation)
    {
        float dp = Cell::edge_length + cell_interval;
        position -= dp;
        for (int x = 0; x < 3; ++x)
            for (int y = 0; y < 3; ++y)
                for (int z = 0; z < 3; ++z) {
                    cells[x][y][z] = Cell(
                        Vec3 {
                            position.x + x * dp,
                            position.y + y * dp,
                            position.z + z * dp
                        },
                        glm::angleAxis(0.f, 0.f, 0.f, 1.f)
                        // Quat(Vec3(1.57f, 1.57f, 0.f))
                    );
                    cells[x][y][z].add_effect(new Rotation<Cell>(4., glm::angleAxis(90.f, 0.f, 0.f, 1.f)));
                }
    }
    virt draw() -> void {
        Cell* cells_ptr = &cells[0][0][0];
        for (int i = 0; i < 27; ++i) {
            (cells_ptr + i)->draw();
        }
    }
    virt update(float delta) -> void {
        GameObjectTemplate::update(delta);
        Cell* cells_ptr = &cells[0][0][0];
        for (int i = 0; i < 27; ++i) {
            (cells_ptr + i)->update(delta);
        }
    }
};

float Cube::cell_interval = 0.05;

#endif GAME_OBJECTS_CUBE_HPP