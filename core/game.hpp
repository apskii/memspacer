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
    GLuint
        shader_program,
        mv_var,
        mvp_var,
        scale_var,
        color_var,
        light_position_var,
        light_intensity_var,
        k_diffuse_var,
        k_ambient_var,
        k_specular_var,
        shininess_var;
    Mat4 view;
    Mat4 proj;
    RenderContext(GLuint shader_program, const Mat4& view, const Mat4& proj)
        : shader_program(shader_program)
        , view(view)
        , proj(proj)
    {
        mv_var = glGetUniformLocation(shader_program, "mv");
        mvp_var = glGetUniformLocation(shader_program, "mvp");
        scale_var = glGetUniformLocation(shader_program, "scale");
        color_var = glGetUniformLocation(shader_program, "color");
        light_position_var = glGetUniformLocation(shader_program, "light_position");
        light_intensity_var = glGetUniformLocation(shader_program, "light_intensity");
        k_diffuse_var = glGetUniformLocation(shader_program, "k_diffuse");
        k_ambient_var = glGetUniformLocation(shader_program, "k_ambient");
        k_specular_var = glGetUniformLocation(shader_program, "k_specular");
        shininess_var = glGetUniformLocation(shader_program, "shininess");
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
            glm::lookAt(Vec3(0.f, 0.f, -3.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f)),
            glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10.0f)
        )
    {}
    meth activate() -> void {
        glUniform3f(render_ctx.light_position_var, 0, 2, -20);
        glUniform3f(render_ctx.light_intensity_var, 0.3, 0, 1.0);
        glUniform3f(render_ctx.k_diffuse_var, 1, 1, 1);
        glUniform3f(render_ctx.k_ambient_var, 0.8, 0.8, 0.8);
        glUniform3f(render_ctx.k_specular_var, 1, 1, 0);
        glUniform1f(render_ctx.shininess_var, 1);
    }
    meth render() -> void {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    val window = glfwCreateWindow(1920, 1080, "memspacer", glfwGetPrimaryMonitor(), NULL);
    // val window = glfwCreateWindow(640, 480, "memspacer", NULL, NULL);
    if (!window) die();
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int) -> void {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwDestroyWindow(window);
            die();
        }
    });
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (glewInit() != GLEW_OK) die();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    val shader_program = load_shaders();
    glUseProgram(shader_program);
    return make_tuple(window, shader_program);
}

func run() -> void {
    val ogl_info = init_ogl();
    var game_ctx = GameContext(get<0>(ogl_info), get<1>(ogl_info));
    //////////////////////////////////////////////////////////////////////////
    var& p = game_ctx.effect_pool;
    typedef Cube<RenderContext> C;
    var* effect
        = (rotation<C>(2, glm::angleAxis(+90.f, 0.f, 1.f, 0.f), p)
        >> rotation<C>(2, glm::angleAxis(+90.f, 0.f, 0.f, 1.f), p)
        >> rotation<C>(2, glm::angleAxis(-90.f, 0.f, 1.f, 0.f), p)
        // || rotation<C>(2, glm::angleAxis(270.f, 1.f, 0.f, 0.f), p)
        ).eval(p);
    game_ctx.cube.attach_effect(effect);
    ///////////////////////////////////////////////////////////////////////////
    game_ctx.activate();
    float cur_time = glfwGetTime();
    for (;;) {
        float new_time = glfwGetTime();
        float delta = new_time - cur_time;
        cur_time = new_time;
        game_ctx.render();
        game_ctx.update(delta);
        glfwPollEvents();
    }
}

func die() -> void {
    glfwTerminate();
    exit(EXIT_FAILURE);
}

}}
#endif CORE_GAME_HPP