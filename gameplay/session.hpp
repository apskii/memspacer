#ifndef CORE_GAMEPLAY_SESSION
#define CORE_GAMEPLAY_SESSION

#include <vector>
#include <chrono>
#include <random>
#include "../core/defs.hpp"
#include "cue.hpp"
#include "../actions/show_cues.hpp"
#include "../actions/wait_response.hpp"
#include "../actions/dance.hpp"

struct Cube;

namespace gameplay {
    class Session {
        enum State { Start, ShowCues, WaitResponse, End };
    public:
        Cube& cube;
        int score;
        Session(Cube& cube, std::vector<Cue> cues)
            : rnd_gen(std::chrono::system_clock::now().time_since_epoch().count())
            , action_pool(32)
            , cube(cube)
            , cues(cues)
            , steps(20)
            , back_n(2)
            , cues_n(2)
        {
            cur_action = new (action_pool.malloc()) actions::Dance(rnd_gen());
            state = Start;
        }
        meth process(float delta) -> bool {
            if (!cur_action->process(*this, delta)) {
                action_pool.free(&cur_action);
                if (state == End)
                    return false;
                if (state == ShowCues) {
                    cur_action = new (action_pool.malloc()) actions::WaitResponse();
                }
                else {
                    if (state == WaitResponse) --steps;
                    if (steps == 0) {
                        cur_action = new (action_pool.malloc()) actions::Dance(rnd_gen());
                        /*show scoreboard*/
                    }
                    else {
                        cur_action = new (action_pool.malloc()) actions::ShowCues();
                    }
                }
            }
            return true;
        }
    private:
        const int back_n;
        const int cues_n;
        int steps;
        State state;
        std::vector<Cue> cues;
        Pool action_pool;
        Action* cur_action;
        std::mt19937 rnd_gen;
    };
}

#endif CORE_GAMEPLAY_SESSION