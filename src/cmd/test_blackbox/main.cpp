/**
 * @copyright 2021 YelloSoft
 */

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

#include "blackbox/blackbox.hpp"

static void panic(const std::string &label, const std::string &message) {
    std::cerr << label << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

static void test_algorithm_shallow(const std::string &label, const std::function<std::tuple<uint64_t, uint64_t>(uint64_t)> &a) {
    if (a(0UL) != std::make_tuple(0UL, 0UL)) {
        panic(label, "expected null factoring");
    }

    for (auto n = 1UL; n < 4UL; n++) {
        if (a(n) != std::make_tuple(n, 1UL)) {
            panic(label, "expected base case -> (n, 1)");
        }
    }

    if (a(4UL) != std::make_tuple(2UL, 2UL)) {
        panic(label, "expected 4 -> (2, 2)");
    }
    if (a(5UL) != std::make_tuple(5UL, 1UL)) {
        panic(label, "expected 5 -> (5, 1)");
    }
    if (a(6UL) != std::make_tuple(2UL, 3UL)) {
        panic(label, "expected 6 -> (2, 3)");
    }

    for (auto n = 4UL; n < 1000; n += 2) {
        if (a(n) != std::make_tuple(2, n / 2)) {
            panic(label, "expected 2q -> (2, q)");
        }
    }
}

static void test_algorithm_deep(const std::string &label, const std::function<std::tuple<uint64_t, uint64_t>(uint64_t)> &a, const blackbox::sieve &sv) {
    for (const auto p : sv.odd_primes) {
        if (a(p) != std::make_tuple(p, 1UL)) {
            panic(label, "expected p -> (p, 1)");
        }
    }

    for (const auto p : sv.odd_primes) {
        const auto n = p * p;
        if (a(n) != std::make_tuple(p, p)) {
            panic(label, "expected p^2 -> (p, p)");
        }
    }

    for (auto n = 1UL; n < sv.index; n++) {
        const auto [p, q] = a(n);

        if (p * q != n) {
            panic(label, "invalid factoring");
        }
    }
}

int main() {
    test_algorithm_shallow("bruteforce", blackbox::factor_bruteforce);
    test_algorithm_shallow("odd_linear", blackbox::factor_odd_linear);
    test_algorithm_shallow("default", blackbox::factor);

    blackbox::sieve sv{};

    for (auto i = 0; i < 100; i++) {
        sv.grow();
    }

    test_algorithm_deep("default", blackbox::factor, sv);
    return EXIT_SUCCESS;
}
