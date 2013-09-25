#ifndef GAME_OBJECTS_CUBE_HPP
#define GAME_OBJECTS_CUBE_HPP

#include "../core/game_object.hpp"
#include "cell.hpp"

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
                        Quat { 0, 0, 0, 0 }
                    );
                }
    }
    virt draw() -> void {
        Cell* cells_ptr = &cells[0][0][0];
        for (int i = 0; i < 27; ++i) {
            (cells_ptr + i)->draw();
        }
    }
};

float Cube::cell_interval = 0.05;

#endif GAME_OBJECTS_CUBE_HPP