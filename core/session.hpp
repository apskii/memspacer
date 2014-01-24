#pragma once

#include "defs.hpp"
#include "configuration.hpp"
#include "../effect/algebra.hpp"
#include "../effects/blink.hpp"
#include "../effects/rotation.hpp"
#include "../game_objects/cube.hpp"
#include "../game_objects/cell.hpp"
#include "effect.hpp"
#include "game_sig.hpp"
#include <list>

namespace core {
    class Session {
        enum State { Activation, Delay };
        enum Cue { Position, Color, Sound };
    public:
        Session()
            : rounds(20)
            , state(Delay)
        {}
        void update(Game& game_ctx, float delta) {
            using namespace game_objects;
            using namespace effects;
            auto& pool = game_ctx.effect_pool;
            state_time += delta;
            if (state == Activation) {
                if (state_time >= game_ctx.config.blink_time) {
                    state = Delay;
                    state_time = 0;
                    int movement = rand() % 2; //(4 + 2 * game_ctx.config.use_z_rot);
                    switch (movement) {
                        case 0: turn_left(game_ctx); break;
                        case 1: turn_right(game_ctx); break;
                        case 2: turn_up(game_ctx); break;
                        case 3: turn_down(game_ctx); break;
                        case 4: turn_z_left(game_ctx); break;
                        case 5: turn_z_right(game_ctx); break;
                    }
                }
            } else {
                if (state_time >= game_ctx.config.interval) {
                    state = Activation;
                    state_time = 0;
                    int cell_ix_ix = rand() % 9;
                    if (positions.size() == game_ctx.config.buff_len)
                        positions.pop_back();
                    positions.push_front(cell_ix_ix);
                    auto cell_ix = face_vertex_index[0][cell_ix_ix];
                    auto& cell = game_ctx.cube.cells[cell_ix[0]][cell_ix[1]][cell_ix[2]];
                    std::cout << cell_ix[0] << "; " << cell_ix[1] << "; " << cell_ix[2] << std::endl;
                    auto bt = 0.5;
                    auto highligh = blink<Cell<Cube>>(bt, Vec4(0.0f, 1.0f, 0.6f, 1.0f), pool)
                                 >> blink<Cell<Cube>>(bt, cell.color, pool);
                    cell.attach_effect(highligh.eval(pool));
                    if (!--rounds) {
                        std::cout << "game over!" << std::endl;
                        game_ctx.kill();
                    };
                }
            }
        }
        void signalize_cue(Cue cue) {

        }
    private:
        std::list<int> positions;
        std::list<char> letters;
        int rounds;
        State state;
        float state_time;

        std::vector<std::vector<std::vector<int>>> face_vertex_index = {
            // Front[0], Back[1]
            { {0,2,0}, {1,2,0}, {2,2,0}, {0,1,0}, {1,1,0}, {2,1,0}, {0,0,0}, {1,0,0}, {2,0,0} },
            { {2,2,2}, {1,2,2}, {0,2,2}, {2,1,2}, {1,1,2}, {0,1,2}, {2,0,2}, {1,0,2}, {0,0,2} },
            // Left[2], Right[3]
            { {0,2,2}, {0,2,1}, {0,2,0}, {0,1,2}, {0,1,1}, {0,1,0}, {0,0,2}, {0,0,1}, {0,0,0} },
            { {2,2,0}, {2,2,1}, {2,2,2}, {2,1,0}, {2,1,1}, {2,1,2}, {2,0,0}, {2,0,1}, {2,0,2} },
            // Up[4], Down[5]
            { {0,2,2}, {1,2,2}, {2,2,2}, {0,2,1}, {1,2,1}, {2,2,1}, {0,2,0}, {1,2,0}, {2,2,0} },
            { {0,0,0}, {1,0,0}, {2,0,0}, {0,0,1}, {1,0,1}, {2,0,1}, {0,0,2}, {1,0,2}, {2,0,2} }
        };

        void turn_left(Game& game_ctx) {
            std::cout << "r/left" << std::endl;
            game_ctx.cube.attach_effect(
                new (game_ctx.effect_pool.malloc()) effects::Rotation<game_objects::Cube>(
                    game_ctx.config.interval * 0.75,
                    glm::angleAxis(90.f, 0.f, 1.f, 0.f))
            );
            ar_rotate_right(face_vertex_index[4]);
            ar_rotate_left(face_vertex_index[5]);
            auto& fvi = face_vertex_index;
            auto fvi0 = fvi[0]; auto fvi1 = fvi[1]; auto fvi2 = fvi[2]; auto fvi3 = fvi[3];
            fvi[0] = fvi3; fvi[1] = fvi2; fvi[2] = fvi0; fvi[3] = fvi1;
        }

        void turn_right(Game& game_ctx) {
            std::cout << "r/right" << std::endl;
            game_ctx.cube.attach_effect(
                new (game_ctx.effect_pool.malloc()) effects::Rotation<game_objects::Cube>(
                    game_ctx.config.interval * 0.75,
                    glm::angleAxis(-90.f, 0.f, 1.f, 0.f))
            );
            ar_rotate_left(face_vertex_index[4]);
            ar_rotate_right(face_vertex_index[5]);
            auto& fvi = face_vertex_index;
            auto fvi0 = fvi[0], fvi1 = fvi[1], fvi2 = fvi[2], fvi3 = fvi[3];
            fvi[0] = fvi2; fvi[1] = fvi3; fvi[2] = fvi1; fvi[3] = fvi0;
        }

        void turn_up(Game& game_ctx) {
            std::cout << "r/up" << std::endl;
            game_ctx.cube.attach_effect(
                new (game_ctx.effect_pool.malloc()) effects::Rotation<game_objects::Cube>(
                    game_ctx.config.interval * 0.75,
                    glm::angleAxis(-90.f, 1.f, 0.f, 0.f))
            );
            ar_rotate_left(face_vertex_index[2]);
            ar_rotate_right(face_vertex_index[3]);
            auto& fvi = face_vertex_index;
            auto fvi0 = fvi[0], fvi1 = fvi[1], fvi4 = fvi[4], fvi5 = fvi[5];
            fvi[0] = fvi5; fvi[1] = fvi4; fvi[4] = fvi0; fvi[5] = fvi1;
        }

        void turn_down(Game& game_ctx) {
            std::cout << "r/down" << std::endl;
            game_ctx.cube.attach_effect(
                new (game_ctx.effect_pool.malloc()) effects::Rotation<game_objects::Cube>(
                    game_ctx.config.interval * 0.75,
                    glm::angleAxis(90.f, 1.f, 0.f, 0.f))
            );
            ar_rotate_right(face_vertex_index[2]);
            ar_rotate_left(face_vertex_index[3]);
            auto& fvi = face_vertex_index;
            auto fvi0 = fvi[0], fvi1 = fvi[1], fvi4 = fvi[4], fvi5 = fvi[5];
            fvi[0] = fvi4; fvi[1] = fvi5; fvi[4] = fvi1; fvi[5] = fvi0;
        }
            // Front[0], Back[1]
                 // Left[2], Right[3]
            // Up[4], Down[5]

        void turn_z_left(Game& game_ctx) {
            // todo
        }

        void turn_z_right(Game& game_ctx) {
            // todo
        }

        static void ar_rotate_left(std::vector<std::vector<int>>& xs) {
            auto tmp = xs[0];
            xs[0] = xs[2];
            auto xs6 = xs[6];
            xs[6] = tmp;
            tmp = xs6;
            auto xs8 = xs[8];
            xs[8] = tmp;
            tmp = xs8;
            xs[2] = tmp;
            tmp = xs[1];
            xs[1] = xs[5];
            auto xs3 = xs[3];
            xs[3] = tmp;
            tmp = xs3;
            auto xs7 = xs[7];
            xs[7] = tmp;
            xs[5] = xs7;
        }

        static void ar_rotate_right(std::vector<std::vector<int>>& xs) {
            auto tmp = xs[0];
            xs[0] = xs[6];
            auto xs2 = xs[2];
            xs[2] = tmp;
            tmp = xs2;
            auto xs8 = xs[8];
            xs[8] = tmp;
            tmp = xs8;
            xs[6] = tmp;
            tmp = xs[1];
            xs[1] = xs[3];
            auto xs5 = xs[5];
            xs[5] = tmp;
            tmp = xs5;
            auto xs7 = xs[7];
            xs[7] = tmp;
            tmp = xs7;
            xs[3] = tmp;
        }

        static int ix_shift_left(int ix) {
            return (ix == 0 || ix == 3 || ix == 6)
                ? ix + 2
                : ix - 1;
        }

        static int ix_shift_right(int ix) {
            return (ix == 2 || ix == 5 || ix == 8)
                ? ix - 2
                : ix + 1;
        }

        static int ix_shift_up(int ix) {
            return (ix < 3)
                ? ix + 6
                : ix - 3;
        }

        static int ix_shift_down(int ix) {
            return (ix > 5)
                ? ix - 6
                : ix + 3;
        }
    };
}
