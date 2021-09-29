#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>

#include "blackbox/blackbox.hpp"

std::ostream &operator<<(std::ostream &o, const std::tuple<uint64_t, uint64_t> &n) {
    const auto [p, q] = n;
    return o << "(" << p << ", " << q << ")";
}

namespace blackbox {
std::optional<std::tuple<uint64_t, uint64_t>> factor_bruteforce(uint64_t n) {
    if (n < 4UL) {
        return std::nullopt;
    }

    const auto root = sqrt(n);

    for (auto p = 2UL; p <= root; p++) {
        if (n % p == 0UL) {
            const auto q = n / p;
            return std::optional(std::make_tuple(p, q));
        }
    }

    return std::nullopt;
}

void sieve::grow() {
    index++;

    bool prime = true;

    for (const auto p : primes) {
        if (index % p == 0UL) {
            prime = false;
            break;
        }
    }

    if (prime) {
        primes.push_back(index);
    }
}

std::optional<std::tuple<uint64_t, uint64_t>> factor_sieve(uint64_t n) {
    if (n < 4UL) {
        return std::nullopt;
    }

    const auto root = sqrt(n);

    sieve s{};

    auto p = 2UL;

    do {
        p = s.primes.back();

        if (n % p == 0UL) {
            const auto q = n / p;
            return std::optional(std::make_tuple(p, q));
        }

        s.grow();
    } while (p <= root);

    return std::nullopt;
}

std::optional<std::tuple<uint64_t, uint64_t>> factor(uint64_t n) {
    return factor_sieve(n);
}
}
