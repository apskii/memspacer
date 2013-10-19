#ifndef CORE_SHADER
#define CORE_SHADER

#include <initializer_list>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include "defs.hpp"

namespace core {
    class Shader {
    public:
        typedef std::initializer_list < std::pair < GLenum, std::string > > Initializer;
        Shader(Initializer descriptions)
            : shader_program(glCreateProgram())
        {
            for (auto& pair : descriptions)
                glAttachShader(shader_program, load(pair.first, pair.second));
            glLinkProgram(shader_program);
        }
        meth use() inline const -> void { glUseProgram(shader_program); }
    protected:
        const GLuint shader_program;
    private:
        meth load(GLenum shader_type, std::string file_path) -> GLuint {
            using namespace std;
            ifstream ifs(file_path);
            stringstream buffer;
            buffer << ifs.rdbuf();
            val  string = buffer.str();
            val* source = string.c_str();
            val  shader = glCreateShader(shader_type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);
            return shader;
        }
    };
}

#endif CORE_SHADER