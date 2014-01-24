#pragma once

#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include "defs.hpp"
#include "render_context.hpp"
#include "configuration.hpp"
#include "effect.hpp"
#include "../effect/algebra.hpp"
#include "../game_objects/cube.hpp"
#include "../game_objects/star_nest.hpp"
#include "game_sig.hpp"
#include "session.hpp"

namespace core {
    Game::Game(GLFWwindow* window, Configuration cfg)
        : window(window)
        , config(cfg)
        , cube(Vec3(0.f, 0.f, 0.f), glm::angleAxis(0.f, 0.f, 0.f, 1.f))
        , effect_pool(40)
        , session(new Session())
        , render_ctx(
            glm::lookAt(Vec3(0.f, 0.f, -3.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f)),
            glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10.0f)
        )
    {
        auto& def_s = render_ctx.default_shader;
        def_s.use();
        glUniform3f(def_s.light_position, 0, 2, -20);
        glUniform3f(def_s.light_intensity, 0.3, 0, 1.0);
        glUniform3f(def_s.k_diffuse, 1, 1, 1);
        glUniform3f(def_s.k_ambient, 0.8, 0.8, 0.8);
        glUniform3f(def_s.k_specular, 1, 1, 0);
        glUniform1f(def_s.shininess, 1);
        auto& star_s = render_ctx.star_nest_shader;
        star_s.use();
        glUniform2f(star_s.resolution, 640, 480);
        auto view_proj = render_ctx.proj * render_ctx.view;
        glUniformMatrix4fv(star_s.view_proj, 1, GL_FALSE, &view_proj[0][0]);
        // ...
        config.blink_time = 1;
        config.interval = 2;
    }

    void Game::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.render(render_ctx);
        if (config.use_space_bg)
            star_nest.render(render_ctx);
        glfwSwapBuffers(window);
    }

    void Game::update(float delta) {
        session->update(*this, delta);
        render_ctx.global_time += delta;
        cube.update(delta, effect_pool);
    }

    GLFWwindow* Game::init_ogl() {
        glfwSetErrorCallback([](int error, const char* description) -> void {
            fputs(description, stderr);
        });
        if (!glfwInit()) exit(EXIT_FAILURE);
        auto window = glfwCreateWindow(1366, 768, "memspacer", glfwGetPrimaryMonitor(), NULL);
        // val window = glfwCreateWindow(640, 480, "memspacer", NULL, NULL);
        if (!window) kill();
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int) -> void {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwDestroyWindow(window);
                kill();
            }
        });
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        if (glewInit() != GLEW_OK) kill();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        return window;
    }

    int Game::run(const core::Configuration& cfg) {
        Game game_ctx(init_ogl(), cfg);
        float cur_time = glfwGetTime();
        for (;;) {
            float new_time = glfwGetTime();
            float delta = new_time - cur_time;
            cur_time = new_time;
            game_ctx.render();
            game_ctx.update(delta);
            glfwPollEvents();
        }
        return 0;
    }

    void Game::kill() {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

/*
namespace core {
    class Game {
    public:
        GLFWwindow* window;
        Configuration config;
        Pool effect_pool;
        RenderContext render_ctx;
        Session<Game> session;
        game_objects::Cube cube;
        game_objects::StarNest star_nest;
    private:
        Game(GLFWwindow* window, Configuration cfg)
            : window(window)
            , config(cfg)
            , cube(Vec3(0.f, 0.f, 0.f), glm::angleAxis(0.f, 0.f, 0.f, 1.f))
            , effect_pool(40)
            , render_ctx(
                glm::lookAt(Vec3(0.f, 0.f, -3.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f)),
                glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10.0f)
            )
        {
            auto& def_s = render_ctx.default_shader;
            def_s.use();
            glUniform3f(def_s.light_position, 0, 2, -20);
            glUniform3f(def_s.light_intensity, 0.3, 0, 1.0);
            glUniform3f(def_s.k_diffuse, 1, 1, 1);
            glUniform3f(def_s.k_ambient, 0.8, 0.8, 0.8);
            glUniform3f(def_s.k_specular, 1, 1, 0);
            glUniform1f(def_s.shininess, 1);
            auto& star_s = render_ctx.star_nest_shader;
            star_s.use();
            glUniform2f(star_s.resolution, 640, 480);
            auto view_proj = render_ctx.proj * render_ctx.view;
            glUniformMatrix4fv(star_s.view_proj, 1, GL_FALSE, &view_proj[0][0]);
            // ...
            config.blink_time = 2;
            config.interval = 2;
        }
        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            cube.render(render_ctx);
            if (config.use_space_bg)
              star_nest.render(render_ctx);
            glfwSwapBuffers(window);
        }
        void update(float delta) {
            session.update(*this, delta);
            render_ctx.global_time += delta;
            cube.update(delta, effect_pool);
        }
        static GLFWwindow* init_ogl() {
            glfwSetErrorCallback([](int error, const char* description) -> void {
                fputs(description, stderr);
            });
            if (!glfwInit()) exit(EXIT_FAILURE);
            auto window = glfwCreateWindow(1366, 768, "memspacer", glfwGetPrimaryMonitor(), NULL);
            // val window = glfwCreateWindow(640, 480, "memspacer", NULL, NULL);
            if (!window) kill();
            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int) -> void {
                if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                    glfwDestroyWindow(window);
                    kill();
                }
            });
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            if (glewInit() != GLEW_OK) kill();
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            return window;
        }
    public:
        static int run(const core::Configuration& cfg) {
            Game game_ctx(init_ogl(), cfg);
            float cur_time = glfwGetTime();
            for (;;) {
                float new_time = glfwGetTime();
                float delta = new_time - cur_time;
                cur_time = new_time;
                game_ctx.render();
                game_ctx.update(delta);
                glfwPollEvents();
            }
            return 0;
        }
        static void kill() {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    };
}
*/
