#ifndef CORE_GAMEPLAY_SESSION
#define CORE_GAMEPLAY_SESSION

#include <vector>
#include <chrono>
#include <random>
#include "../defs.hpp"
#include "cue.hpp"
#include "../../actions/show_cues.hpp"
#include "../../actions/wait_response.hpp"
#include "../../actions/dance.hpp"

struct Cube;

struct Session {
    Cube& cube;
    int score;
    Session(Cube& cube, std::vector<Cue> cues)
        : rnd_gen(std::chrono::system_clock::now().time_since_epoch().count())
        , action_pool(32)
        , cube(cube)
        , cues(cues)
    {
        cur_action = new (action_pool.malloc()) Dance(rnd_gen());
        state = StartState;
    }
    meth process(float delta) -> bool {
        if (!cur_action->process(*this, delta)) {
            action_pool.free(&cur_action);
            if (state == EndState) {
                /* */
            } else if (state != ReqState) {
                if (/*end of game*/0) {
                    cur_action = new (action_pool.malloc()) Dance(rnd_gen());
                    /*show scoreboard*/
                }
                else {
                    cur_action = new (action_pool.malloc()) ShowCues();                    
                }
            }

        }
        // ShowCues()
        return false;
    }
private:
    const int back_n = 1;
    const int cues_n = 2;
    enum { ReqState, RespState, StartState, EndState } state;
    std::vector<Cue> cues;
    Pool action_pool;
    Action* cur_action;
    std::mt19937 rnd_gen;
};

#endif CORE_GAMEPLAY_SESSION