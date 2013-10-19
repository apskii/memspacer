#ifndef GAME_OBJECTS_STAR_NEST
#define GAME_OBJECTS_STAR_NEST

#include "../core/defs.hpp"
#include "../core/game_object.hpp"

namespace game_objects {
    struct StarNestVertices {
        GLuint vbo;
        StarNestVertices() {
            static const GLfloat vertices [] = {
                +3, -3, +1,
                -3, +3, +1,
                -3, -3, +1,
                +3, -3, +1,
                +3, +3, +1,
                -3, +3, +1
            };
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        }
    };

    TPL(RenderContext) struct StarNest : core::GameObjectTemplate<StarNest<RenderContext>, RenderContext> {
        StarNest() : GameObjectTemplate() {}
        virt render(const RenderContext& ctx) -> void {
            static StarNestVertices star_nest_vertices;
            ctx.star_nest_shader.use();
            glUniform1f(ctx.star_nest_shader.global_time, ctx.global_time);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, star_nest_vertices.vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glDisableVertexAttribArray(0);
        }
    };
}

#endif GAME_OBJECTS_STAR_NEST