#ifndef CORE_GAMEPLAY_ACTION
#define CORE_GAMEPLAY_ACTION

#include "../defs.hpp"
#include "../generic/behaviour.hpp"
#include "../generic/pooled.hpp"

struct GameState;

struct Action : Pooled, Behaviour<GameState> {};

TPL(Action) struct CheckAction {
    static_assert(sizeof(Action) <= 32,
        "Action subclasses should have sizeof <= 32 to fit into object pools."
    );
};

#define CHECK_ACTION(NAME, TYPE) struct NAME ## Checker : public CheckAction<TYPE> {}

#endif CORE_GAMEPLAY_ACTION