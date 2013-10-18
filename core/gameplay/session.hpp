#ifndef CORE_GAMEPLAY_SESSION
#define CORE_GAMEPLAY_SESSION

#include <vector>
#include "../defs.hpp"
#include "cue.hpp"
#include "../../actions/show_cues.hpp"
#include "../../actions/wait_response.hpp"

struct Session {
    int back_n;
    int cues_n;
    std::vector<Cue> cues;
    meth process() -> bool {
        ShowC
        return false;
    }
};

#endif CORE_GAMEPLAY_SESSION