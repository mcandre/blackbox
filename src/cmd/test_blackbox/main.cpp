/**
 * @copyright 2021 YelloSoft
 */

#include <cstdint>
#include <functional>
#include <iostream>

#include "blackbox/blackbox.hpp"

static void panic(const std::string &label, const std::string &message) {
    std::cerr << label << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

static void test_algorithm_shallow(const std::string &label, const std::function<__uint128_t(__uint128_t)> &a) {
    if (a(15) == 0) {
        panic(label, "expected a(15) != 0");
    }
}

int main() {
    blackbox::sieve sv{};
    test_algorithm_shallow("sieve", [&](__uint128_t n) mutable { return sv.factor(n); });
    return EXIT_SUCCESS;
}
