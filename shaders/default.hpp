#ifndef SHADERS_DEFAULT
#define SHADERS_DEFAULT

#include "../core/defs.hpp"
#include "../core/shader.hpp"

namespace shaders {
    struct Default : core::Shader {
        GLuint mv, mvp, scale, color,
               light_position, light_intensity,
               k_diffuse, k_ambient, k_specular,
               shininess;
        Default(Initializer descriptions)
            : core::Shader(descriptions)
        {
            mv = glGetUniformLocation(shader_program, "mv");
            mvp = glGetUniformLocation(shader_program, "mvp");
            scale = glGetUniformLocation(shader_program, "scale");
            color = glGetUniformLocation(shader_program, "color");
            light_position = glGetUniformLocation(shader_program, "light_position");
            light_intensity = glGetUniformLocation(shader_program, "light_intensity");
            k_diffuse = glGetUniformLocation(shader_program, "k_diffuse");
            k_ambient = glGetUniformLocation(shader_program, "k_ambient");
            k_specular = glGetUniformLocation(shader_program, "k_specular");
            shininess = glGetUniformLocation(shader_program, "shininess");
        }
    };
}

#endif SHADERS_DEFAULT