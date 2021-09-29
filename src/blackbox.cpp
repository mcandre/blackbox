#include <algorithm>
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

    for (auto p = 2UL; p < n; p++) {
        if (n % p == 0UL) {
            const auto q = n / p;
            return std::optional(std::make_tuple(p, q));
        }
    }

    return std::nullopt;
}

std::optional<std::tuple<uint64_t, uint64_t>> factor_odd_linear(uint64_t n) {
    if (n < 4UL) {
        return std::nullopt;
    }

    if (n % 2UL == 0) {
        return std::make_tuple(2UL, n / 2UL);
    }

    const auto root = uint64_t(sqrt(n));

    for (auto p = 3UL; p <= root; p += 2) {
        if (n % p == 0UL) {
            const auto q = n / p;
            return std::optional(std::make_tuple(p, q));
        }
    }

    return std::nullopt;
}

void sieve::grow() {
    index += 2;

    if (index % 2 == 0UL) {
        return;
    }

    bool prime = true;

    const auto root = uint64_t(index);
    const auto sz = odd_primes.size();

    for (auto i = size_t(0); i < sz; i++) {
        const auto p = odd_primes[i];

        if (index % p == 0UL) {
            prime = false;
            break;
        }

        if (p > root) {
            break;
        }
    }

    if (prime) {
        odd_primes.push_back(index);
    }
}

std::optional<std::tuple<uint64_t, uint64_t>> sieve::factor(uint64_t n) {
    if (n % 2 == 0UL) {
        return std::optional(std::make_tuple(2UL, n / 2UL));
    }

    const auto root = uint64_t(sqrt(n));
    const auto sz = odd_primes.size();

    for (auto i = size_t(0); i <= root && i < sz; i++) {
        const auto p = odd_primes[i];

        if (n == p) {
            return std::nullopt;
        }

        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    }

    while (index <= root) {
        grow();

        const auto last_known_prime = odd_primes.back();

        if (n % last_known_prime == 0UL) {
            return std::make_tuple(last_known_prime, n / last_known_prime);
        }
    }

    return std::nullopt;
}

std::optional<std::tuple<uint64_t, uint64_t>> factor(uint64_t n) {
    if (n < 4UL) {
        return std::nullopt;
    }

    sieve sv{};
    return sv.factor(n);
}
}
