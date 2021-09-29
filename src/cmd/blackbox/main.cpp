#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "blackbox/blackbox.hpp"

static void usage(const char *program) {
    std::cerr << "Usage: " << program << " <positive integer>" << std::endl;
}

int main(int argc, char **argv) {
    const auto *program = argv[0];

    if (argc != 2) {
        usage(program);
        return EXIT_FAILURE;
    }

    auto n = 0UL;

    try {
        n = std::stoul(argv[1]);
    } catch (std::invalid_argument &e) {
        usage(program);
        return EXIT_FAILURE;
    }

    const auto result = blackbox::factor(n);

    if (!result.has_value()) {
        usage(program);
        return EXIT_FAILURE;
    }

    std::cout << *result << std::endl;
    return EXIT_SUCCESS;
}
