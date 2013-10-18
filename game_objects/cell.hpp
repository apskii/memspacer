#ifndef GAME_OBJECTS_CELL_HPP
#define GAME_OBJECTS_CELL_HPP

#include "../core/defs.hpp"
#include "../core/game_object.hpp"

namespace game_objects {
    struct CellVertices {
        GLuint ibo;
        GLuint vbo;
        CellVertices() {
            static const GLfloat vertices[24] = {
                -1, -1, -1,
                -1, -1, +1,
                +1, -1, +1,
                +1, -1, -1,
                -1, +1, +1,
                +1, +1, +1,
                -1, +1, -1,
                +1, +1, -1
            };
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            static const GLubyte indices [] = {
                3, 1, 2, 5, 3, 7, 6, 5, 4, 1, 6, 0, 3, 1
            };
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        }
    };

    TPL_2(Owner, RenderContext) class Cell : public core::GameObjectTemplate<Cell<Owner, RenderContext>, RenderContext> {
    private:
        Owner* parent;
    public:
        Vec4 color;
        Cell() {}
        Cell(Owner* parent, Vec3 position, Quat orientation, Vec4 color = Vec4(1.f, 0.f, 0.f, 1.f))
            : GameObjectTemplate(position, orientation)
            , parent(parent)
            , color(color)
        {}
        virt render(const RenderContext& ctx) -> void {
            static CellVertices cell_vertices;
            const Mat4 mv = ctx.view *
                glm::translate(parent->orientation * position) *
                glm::toMat4(orientation * parent->orientation);
            const Mat4 mvp = ctx.proj * mv;
            glUniformMatrix4fv(ctx.mv_var, 1, false, &mv[0][0]);
            glUniformMatrix4fv(ctx.mvp_var, 1, false, &mvp[0][0]);
            glUniform1f(ctx.scale_var, parent->cell_size);
            glUniform4fv(ctx.color_var, 1, &color[0]);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, cell_vertices.vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cell_vertices.ibo);
            glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_BYTE, 0);
            glDisableVertexAttribArray(0);
        }
    };
}

#endif GAME_OBJECTS_CELL_HPP