#pragma once

#include "../core/defs.hpp"
#include "../core/shader.hpp"

namespace shaders {
    struct StarNest : core::Shader {
        GLuint resolution, view_proj, global_time;
        StarNest(Initializer descriptions)
            : core::Shader(descriptions)
        {
            resolution = glGetUniformLocation(shader_program, "resolution");
            view_proj = glGetUniformLocation(shader_program, "view_proj");
            global_time = glGetUniformLocation(shader_program, "global_time");
        }
    };
}
