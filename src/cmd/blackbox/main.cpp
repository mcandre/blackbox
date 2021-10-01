/**
 * @copyright 2021 YelloSoft
 */

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

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

    __uint128_t n = 0;

    try {
        std::stringstream ss;
        ss << std::setw(40) << std::setfill('0') << argv[1];
        const auto n_s = ss.str();
        const auto upper_s = n_s.substr(0, 20);
        const auto lower_s = n_s.substr(20);
        n = (__uint128_t(std::stoul(upper_s)) << __uint128_t(64)) + std::stoul(lower_s);
    } catch (std::out_of_range &e) {
        usage(program);
        return EXIT_FAILURE;
    } catch (std::invalid_argument &e) {
        usage(program);
        return EXIT_FAILURE;
    }

    std::cerr << "N: " << uint64_t(n >> __uint128_t(64)) << uint64_t(n) << std::endl;


    blackbox::sieve sv{};
    std::cout << sv.factor(n) << std::endl;
    return EXIT_SUCCESS;
}
