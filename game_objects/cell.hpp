#ifndef GAME_OBJECTS_CELL_HPP
#define GAME_OBJECTS_CELL_HPP

#include "../core/defs.hpp"
#include "../core/game_object.hpp"

struct Cell : public GameObjectTemplate<Cell> {
    static float edge_length;
    Cell() : Cell(Vec3(), Quat()) {}
    Cell(Vec3 position, Quat orientation)
        : GameObjectTemplate(position, orientation)
    {}
    virt draw() -> void {
        float r = edge_length / 2.f;
        auto& p = this->position;
        auto& o = this->orientation;
        Vec3 vs [] = {
            p + o * Vec3 { -r, -r, -r },
            p + o * Vec3 { -r, -r, +r },
            p + o * Vec3 { +r, -r, +r },
            p + o * Vec3 { +r, -r, -r },
            p + o * Vec3 { -r, +r, +r },
            p + o * Vec3 { +r, +r, +r },
            p + o * Vec3 { -r, +r, -r },
            p + o * Vec3 { +r, +r, -r }
        };
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3fv(&vs[3][0]);
        glVertex3fv(&vs[1][0]);
        glVertex3fv(&vs[2][0]);
        glVertex3fv(&vs[5][0]);
        glVertex3fv(&vs[3][0]);
        glVertex3fv(&vs[7][0]);
        glVertex3fv(&vs[6][0]);
        glVertex3fv(&vs[5][0]);
        glVertex3fv(&vs[4][0]);
        glVertex3fv(&vs[1][0]);
        glVertex3fv(&vs[6][0]);
        glVertex3fv(&vs[0][0]);
        glVertex3fv(&vs[3][0]);
        glVertex3fv(&vs[1][0]);
        glEnd();
    }
};

float Cell::edge_length = 0.3;

#endif GAME_OBJECTS_CELL_HPP