#pragma once

#include "defs.hpp"
#include "render_context.hpp"
#include "configuration.hpp"
#include "../game_objects/cube.hpp"
#include "../game_objects/star_nest.hpp"

namespace core {
    class Session;
    class Game {
    public:
        GLFWwindow* window;
        Configuration config;
        Pool effect_pool;
        RenderContext render_ctx;
        Session* session;
        game_objects::Cube cube;
        game_objects::StarNest star_nest;
    private:
        Game(GLFWwindow* window, Configuration cfg);
        void render();
        void update(float delta);
        static GLFWwindow* init_ogl();
    public:
        static int run(const core::Configuration& cfg);
        static void kill();
    };
}
