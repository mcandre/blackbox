/**
 * @copyright 2021 YelloSoft
 */

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <set>
#include <string>

#include "blackbox/blackbox.hpp"

static void panic(const std::string &label, const std::string &message) {
    std::cerr << label << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

static void test_algorithm_shallow(const std::string &label, const std::function<std::set<uint64_t>(uint64_t)> &a) {
    if (!a(0UL).empty()) {
        panic(label, "expected null factoring");
    }

    if (a(1UL) != std::set<uint64_t>{ 1UL }) {
        panic(label, "expected unity factoring");
    }

    for (auto n = 2UL; n < 4UL; n++) {
        if (a(n) != std::set<uint64_t>{ 1UL, n }) {
            panic(label, "expected base case -> { 1, n }");
        }
    }

    if (a(4UL) != std::set<uint64_t>{ 2UL }) {
        panic(label, "expected 4 -> { 2 }");
    }
    if (a(5UL) != std::set<uint64_t>{ 1UL, 5UL }) {
        panic(label, "expected 5 -> { 1, 5 }");
    }
    if (a(6UL) != std::set<uint64_t>{ 2UL, 3UL }) {
        panic(label, "expected 6 -> { 2, 3 }");
    }

    for (auto n = 4UL; n < 1000; n += 2) {
        if (a(n) != std::set<uint64_t>{ 2, n / 2 }) {
            panic(label, "expected 2q -> { 2, q }");
        }
    }
}

static void test_algorithm_deeper(const std::string &label, const std::function<std::set<uint64_t>(uint64_t)> &a, const std::set<uint64_t> &primes) {
    for (const auto p : primes) {
        if (a(p) != std::set<uint64_t>{ 1UL, p }) {
            panic(label, "expected p -> { 1, p }");
        }
    }

    for (const auto p : primes) {
        const auto n = p * p;
        if (a(n) != std::set<uint64_t>{ p }) {
            panic(label, "expected p^2 ->  { p }");
        }
    }
}

int main() {
    test_algorithm_shallow("sieve", blackbox::factor);

    const blackbox::sieve sv{};
    std::set<uint64_t> primes{ 2UL };
    primes.insert(sv.odd_primes.begin(), sv.odd_primes.end());

    test_algorithm_deeper("sieve", blackbox::factor, primes);
    return EXIT_SUCCESS;
}
