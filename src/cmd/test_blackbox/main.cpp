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
    if (a(4) != 2) {
        panic(label, "expected 4 -> 2");
    }
    if (a(5) != 1) {
        panic(label, "expected 5 -> 1");
    }
    if (a(6) != 2) {
        panic(label, "expected 6 -> 2");
    }
    if (a(15) != 3) {
        panic(label, "expected 15 -> 3");
    }

    for (auto n = __uint128_t(4); n < 1000; n += 2) {
        if (a(n) != 2) {
            panic(label, "expected 2q -> 2");
        }
    }
}

static void test_algorithm_deeper(const std::string &label, const std::function<__uint128_t(__uint128_t)> &a, const std::vector<__uint128_t> &primes) {
    for (const auto p : primes) {
        if (a(p) != 1) {
            panic(label, "expected p -> 1");
        }
    }

    for (const auto p : primes) {
        const auto n = p * p;
        if (a(n) != p) {
            panic(label, "expected p^2 -> p");
        }
    }
}

int main() {
    blackbox::sieve sv{};

    const auto factor_sieve = [&](__uint128_t n) mutable {
        return sv.factor(n);
    };

    test_algorithm_shallow("sieve", factor_sieve);
    test_algorithm_deeper("sieve", factor_sieve, sv.odd_primes);
    return EXIT_SUCCESS;
}
