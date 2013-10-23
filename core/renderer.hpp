#ifndef CORE_RENDERER
#define CORE_RENDERER

#include "defs.hpp"
#include "../shaders/default.hpp"
#include "../shaders/star_nest.hpp"

namespace core {
    struct Renderer {
        shaders::Default default_shader;
        shaders::StarNest star_nest_shader;
        Mat4 view, proj;
        float global_time;
        Renderer(const Mat4& view, const Mat4& proj)
            : default_shader({
                { GL_VERTEX_SHADER, "shaders/glsl/default.v.glsl" },
                { GL_FRAGMENT_SHADER, "shaders/glsl/default.f.glsl" }
            })
            , star_nest_shader({
                { GL_VERTEX_SHADER, "shaders/glsl/star_nest.v.glsl" },
                { GL_FRAGMENT_SHADER, "shaders/glsl/star_nest.f.glsl" }
            })
            , view(view)
            , proj(proj)
            , global_time(0.f)
        {}
    };
}

#endif CORE_RENDERER