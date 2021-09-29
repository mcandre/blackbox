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

    bool prime = true;

    const auto root = uint64_t(index);

    for (auto i = size_t(0); i < primes.size(); i++) {
        const auto p = primes[i];

        if (index % p == 0UL) {
            prime = false;
            break;
        }

        if (p > root) {
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

    if (n % 2 == 0UL) {
        return std::optional(std::make_tuple(2UL, n / 2UL));
    }

    const auto root = uint64_t(sqrt(n));

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
