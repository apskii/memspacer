#pragma once

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
        inline void use() const { glUseProgram(shader_program); }
    protected:
        const GLuint shader_program;
    private:
        GLuint load(GLenum shader_type, std::string file_path) {
            using namespace std;
            ifstream ifs(file_path);
            stringstream buffer;
            buffer << ifs.rdbuf();
            auto  string = buffer.str();
            auto* source = string.c_str();
            auto  shader = glCreateShader(shader_type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);
	    GLint log_length;
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	    GLchar* log = new GLchar[log_length + 1];
	    glGetShaderInfoLog(shader, log_length, NULL, log);
	    cerr << log << endl;
	    delete[] log;
            return shader;
        }
    };
}
