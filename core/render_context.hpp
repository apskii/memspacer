#pragma once

#include "defs.hpp"
#include "../shaders/default.hpp"
#include "../shaders/star_nest.hpp"

namespace core {
    struct RenderContext {
        shaders::Default default_shader;
        shaders::StarNest star_nest_shader;
        Mat4 view, proj;
        float global_time;
        RenderContext(const Mat4& view, const Mat4& proj)
            : default_shader({
                { GL_VERTEX_SHADER, "./default.v.glsl" },
                { GL_FRAGMENT_SHADER, "./default.f.glsl" }
            })
            , star_nest_shader({
                { GL_VERTEX_SHADER, "./star_nest.v.glsl" },
                { GL_FRAGMENT_SHADER, "./star_nest.f.glsl" }
            })
            , view(view)
            , proj(proj)
            , global_time(0.f)
        {}
    };
}
