// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>
#include <algorithm>
#include <GLFW/glfw3.h>
// #include <stdlib.h>
// #include <stdio.h>
#include "core/effect.hpp"
#include "core/effect/algebra.hpp"
#include "game_objects/cell.hpp"
#include "game_objects/cube.hpp"
#include "effects/blink.hpp"
#include "effects/rotation.hpp"

func error_callback(int error, const char* description) -> void {
    fputs(description, stderr);
}

func key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

func test_effect_algebra() -> void {
    auto e = WrapEffectTerm<Cell>{ new Blink<Cell>(0.2, Vec4{ 0, 0, 0, 0 }) };
    Pool effect_pool(32);
    EffectAlgebra effect_algebra(effect_pool);
    auto term = (e || e) >> (e >> (e || e) >> e) >> e;
    std::cout << sizeof(decltype(term));
    effect_algebra.eval((e || e) >> (e >> (e || e) >> e) >> e);
    std::cin.get();
}

func main() -> int {
    // Rotation<Cell> xx(Quat{ 0, 0, 0, 0 });
    Cube c {
        Vec3 { 0.f, 0.f, 0.f },
        Quat { 0.f, 0.f, 0.f, 0.f }
    };
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(1920, 1080, "memspacer", glfwGetPrimaryMonitor(), NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
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
    float curTime = glfwGetTime();
    float angle = 0;
    float delta = 0;
    float min_delta = 100;
    float max_delta = -100;
    while (!glfwWindowShouldClose(window)) {
        float newTime = glfwGetTime();
        float delta = newTime - curTime;
        //if (min_delta > delta) min_delta = delta;
        //if (max_delta < delta) max_delta = delta;
        //if (delta > 0.1) std::cout << max_delta << std::endl;
        curTime = newTime;
        // if (delta < 0.016) continue;
        // angle += std::min(delta, 0.016f) * 100;
        angle += delta * 80;
        // angle += 0.016f * 100;
        // delta = 0;
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(angle, 0.2, 0.6, 0.4);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //glColor3f(1, 1, 1);
        //c.draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 0, 0);
        c.draw();
        c.update(delta);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    // std::cout << min_delta << std::endl << max_delta;
    // std::cin.get();
    exit(EXIT_SUCCESS);
}
// Vec4 v = { 0.0, 0.0, 0.0, 0.0 };
// Blink b(0.5f, v);
// std::cout << sizeof(Blink);
// Chain<Cell> ch(&b, &b);
//std::cin.get();
//return 0;
// Chain<Cell> effect();
// draw_cube(1.f);
/*
glBegin(GL_TRIANGLES);
glColor3f(1.f, 0.f, 0.f);
glVertex3f(-0.6f, -0.4f, 0.f);
glColor3f(0.f, 1.f, 0.f);
glVertex3f(0.6f, -0.4f, 0.f);
glColor3f(0.f, 0.f, 1.f);
glVertex3f(0.f, 0.6f, 0.f);
glEnd();*/