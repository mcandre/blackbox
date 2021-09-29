#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

#include "blackbox/blackbox.hpp"

static void panic(const std::string &label, const std::string &message) {
    std::cerr << label << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

static void test_algorithm(
    const blackbox::sieve &sv,
    const std::string &label,
    const std::function<std::optional<std::tuple<uint64_t, uint64_t>>(uint64_t)> &a) {
    for (auto n = 0UL; n < 4; n++) {
        if (a(n) != std::nullopt) {
            panic(label, "expected base case -> nullopt");
        }
    }

    if (a(5UL) != std::nullopt) {
        panic(label, "expected 5 -> nullopt");
    }
    if (a(6UL) != std::make_tuple(2UL, 3UL)) {
        panic(label, "expected 6 -> (2, 3)");
    }
    if (a(7UL) != std::nullopt) {
        panic(label, "expected 7 -> nullopt");
    }

    for (auto n = 4UL; n < 100; n += 2) {
        if (a(n) != std::make_tuple(2, n / 2)) {
            panic(label, "expected 2q -> (2, q)");
        }
    }

    for (const auto p : sv.primes) {
        if (a(p) != std::nullopt) {
            panic(label, "expected prime -> nullopt");
        }
    }

    for (const auto p : sv.primes) {
        const auto n = p * p;
        if (a(n) != std::make_tuple(p, p)) {
            panic(label, "expected p^2 -> (p, p)");
        }
    }

    for (auto i = size_t(0); i < sv.primes.size() - 1; i++) {
        const auto p = sv.primes[i];

        for (auto j = size_t(i + 1); j < sv.primes.size(); j++) {
            const auto q = sv.primes[j];
            if (a(p * q) != std::make_tuple(p, q)) {
                panic(label, "expected pq -> (p, q)");
            }
        }
    }

    for (auto n = 0UL; n <= sv.index; n++) {
        const auto result = a(n);

        if (result.has_value()) {
            const auto [p, q] = *result;
            if (p * q != n) {
                panic(label, "invalid factoring");
            }
        }
    }
}

int main() {
    blackbox::sieve sv{};

    for (auto i = 0; i < 1000; i++) {
        sv.grow();
    }

    const auto leading_primes = std::vector<uint64_t>(sv.primes.begin(), sv.primes.begin() + 3);
    if (leading_primes != std::vector<uint64_t>{ 2UL, 3UL, 5UL }) {
        panic("sieve", "expected leading primes {2, 3, 5}");
    }

    test_algorithm(sv, "bruteforce", blackbox::factor_bruteforce);
    test_algorithm(sv, "odd_linear", blackbox::factor_odd_linear);
    test_algorithm(sv, "sieve", blackbox::factor_sieve);
    test_algorithm(sv, "default", blackbox::factor);
    return EXIT_SUCCESS;
}
