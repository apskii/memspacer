#include "core/game.hpp"
#include "core/configuration.hpp"
#include <vector>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc + !argc);
    return core::Game::run(core::parse_configuration(args));
}
