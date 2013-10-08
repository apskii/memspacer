#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include "defs.hpp"
#include "../core/effect/algebra.hpp"
#include "../game_objects/cube.hpp"
#include "../effects/rotation.hpp"

namespace memspacer {
namespace game {

using namespace std;

func run() -> void;
func die() -> void;

struct RenderContext {
    GLuint shader_program;
    GLuint mvp_var;
    GLuint scale_var;
    GLuint color_var;
    Mat4 view_proj;
    RenderContext(GLuint shader_program, const Mat4& view_proj)
        : shader_program(shader_program)
        , view_proj(view_proj)
    {
        mvp_var = glGetUniformLocation(shader_program, "mvp");
        scale_var = glGetUniformLocation(shader_program, "scale");
        color_var = glGetUniformLocation(shader_program, "color");
    }
};

struct GameContext {
    GLFWwindow* window;
    Pool effect_pool;
    RenderContext render_ctx;
    Cube<RenderContext> cube;
    GameContext(GLFWwindow* window, GLuint default_shader_program)
        : window(window)
        , cube(Vec3(0.f, 0.f, 0.f), glm::angleAxis(0.f, 0.f, 0.f, 1.f))
        , effect_pool(32)
        , render_ctx(default_shader_program,
            glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f)
          * glm::lookAt(Vec3(0.f, 5.f, 0.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, 1.f))
        )
    {}
    meth render() -> void {
        glClear(GL_COLOR_BUFFER_BIT);
        cube.render(render_ctx);
        glfwSwapBuffers(window);
    }
    meth update(float delta) -> void {
        cube.update(delta, effect_pool);
    }
};

func load_shader(GLenum shader_type, string file_path) -> GLuint {
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

func load_shaders() -> GLuint {
    val program = glCreateProgram();
    glAttachShader(program, load_shader(GL_VERTEX_SHADER, "shaders/default.v.glsl"));
    glAttachShader(program, load_shader(GL_FRAGMENT_SHADER, "shaders/default.f.glsl"));
    glLinkProgram(program);
    return program;
}

func init_ogl() -> tuple<GLFWwindow*, GLuint> {
    glfwSetErrorCallback([](int error, const char* description) -> void {
        fputs(description, stderr);
    });
    if (!glfwInit()) exit(EXIT_FAILURE);
    // window = glfwCreateWindow(1920, 1080, "memspacer", glfwGetPrimaryMonitor(), NULL);
    val window = glfwCreateWindow(640, 480, "memspacer", NULL, NULL);
    if (!window) die();
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwDestroyWindow(window);
            die();
        }
    });
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (glewInit() != GLEW_OK) die();
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    val shader_program = load_shaders();
    glUseProgram(shader_program);
    return make_tuple(window, shader_program);
}

func run() -> void {
    val ogl_info = init_ogl();
    var ctx = GameContext(get<0>(ogl_info), get<1>(ogl_info));
    var& p = ctx.effect_pool;
    var* effect
        = (rotation<Cube<RenderContext>>(2, glm::angleAxis(90.f, 0.f, 0.f, 1.f), p)
        // >> rotation<Cube>(1, glm::angleAxis(90.f, 0.f, 0.f, 1.f), p)
        // || rotation<Cube>(2, glm::angleAxis(270.f, 1.f, 0.f, 0.f), p)
        ).eval(p);
    ctx.cube.attach_effect(effect);
    float cur_time = glfwGetTime();
    for (;;) {
        float new_time = glfwGetTime();
        float delta = new_time - cur_time;
        cur_time = new_time;
        ctx.render();
        ctx.update(delta);
        glfwPollEvents();
    }
}

func die() -> void {
    glfwTerminate();
    exit(EXIT_FAILURE);
}

}}
#endif CORE_GAME_HPP