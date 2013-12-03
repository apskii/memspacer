#pragma once

#include "../core/defs.hpp"

namespace gameplay {
    struct Session;

    struct Action {
        virt free(Pool&) -> void;
        virt process(Session&, float) -> bool;
    };

    TPL(Action) struct CheckAction {
        static_assert(sizeof(Action) <= 32,
            "Action subclasses should have sizeof <= 32 to fit into object pools."
        );
    };
}

#define CHECK_ACTION(NAME, TYPE) struct NAME ## Checker : public gameplay::CheckAction<TYPE> {}
