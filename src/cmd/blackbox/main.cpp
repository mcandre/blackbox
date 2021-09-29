/**
 * @copyright 2021 YelloSoft
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "blackbox/blackbox.hpp"

static void usage(const char *program) {
    std::cerr << "Usage: " << program << " <non-negative integer>" << std::endl;
}

int main(int argc, char **argv) {
    const auto *program = argv[0];

    if (argc != 2) {
        usage(program);
        return EXIT_FAILURE;
    }

    auto n = 0L;

    try {
        n = std::stoul(argv[1]);
    } catch (std::invalid_argument &e) {
        usage(program);
        return EXIT_FAILURE;
    }

    std::cout << blackbox::factor(n) << std::endl;
    return EXIT_SUCCESS;
}
