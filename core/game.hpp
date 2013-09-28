#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <GLFW/glfw3.h>
#include "defs.hpp"
#include "../core/effect/algebra.hpp"
#include "../game_objects/cube.hpp"
#include "../effects/rotation.hpp"

struct Game {
    Cube cube;
    GLFWwindow* window;
    Pool effect_pool;
    Game()
        : cube(Vec3(), glm::angleAxis(0.f, 0.f, 0.f, 1.f))
        , effect_pool(32)
    {
        init();
    }
    meth init() -> void {
        glfwSetErrorCallback([](int error, const char* description) -> void {
            fputs(description, stderr);
        });
        if (!glfwInit())
            exit(EXIT_FAILURE);
        // window = glfwCreateWindow(1920, 1080, "memspacer", glfwGetPrimaryMonitor(), NULL);
        window = glfwCreateWindow(640, 480, "memspacer", NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(EXIT_SUCCESS);
            }
        });
        glfwWindowHint(GLFW_SAMPLES, 4);
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
    }
    meth loop() -> void {
        auto& p = effect_pool;
        auto* effect
            = (rotation<Cube>(3, glm::angleAxis(90.f, 1.f, 0.f, 0.f), p)
            >> rotation<Cube>(3, glm::angleAxis(90.f, 0.f, 0.f, 1.f), p)).eval(p);
        cube.attach_effect(effect);
        float cur_time = glfwGetTime();
        for (;;) {
            float new_time = glfwGetTime();
            float delta = new_time - cur_time;
            cur_time = new_time;
            render();
            update(delta);
            glfwPollEvents();
        }
    }
    meth render() -> void {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 0, 0);
        cube.draw();
        glfwSwapBuffers(window);
    }
    meth update(float delta) -> void {
        cube.update(delta, effect_pool);
    }
};

#endif CORE_GAME_HPP