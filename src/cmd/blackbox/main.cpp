/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>
#include <iostream>

#include "blackbox/blackbox.hpp"

static void usage(const char *program) {
    std::cerr << "Usage: " << program << " <__uint128_t>" << std::endl;
}

int main(int argc, char **argv) {
    const auto *program = argv[0];

    if (argc != 2) {
        usage(program);
        return EXIT_FAILURE;
    }

    blackbox::sieve sv{};

    try {
        std::cout << sv.factor(blackbox::stoulll(argv[1])) << std::endl;
        return EXIT_SUCCESS;
    } catch (std::logic_error &e) {
        usage(program);
        return EXIT_FAILURE;
    }
}
