/**
 * @copyright 2021 YelloSoft
 */

#include <algorithm>
#include <cstdint>
#include <ctgmath>
#include <iostream>
#include <tuple>
#include <vector>

#include "blackbox/blackbox.hpp"

std::ostream &operator<<(std::ostream &o, const std::tuple<uint64_t, uint64_t> &n) {
    const auto [p, q] = n;
    return o << "(" << p << ", " << q << ")";
}

namespace blackbox {
std::tuple<uint64_t, uint64_t> factor_bruteforce(uint64_t n) {
    if (n == 0UL) {
        return NULL_FACTOR;
    }

    if (n < 4UL) {
        return std::make_tuple(n, 1UL);
    }

    for (auto p = 2UL; p < n; p++) {
        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    }

    return std::make_tuple(n, 1UL);
}

std::tuple<uint64_t, uint64_t> factor_odd_linear(uint64_t n) {
    if (n == 0UL) {
        return NULL_FACTOR;
    }

    if (n < 4UL) {
        return std::make_tuple(n, 1UL);
    }

    if (n % 2UL == 0) {
        return std::make_tuple(2UL, n / 2UL);
    }

    const auto root = sqrt(n);

    for (auto p = 3UL; p <= root; p += 2) {
        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    }

    return std::make_tuple(n, 1UL);
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

std::tuple<uint64_t, uint64_t> sieve::factor(uint64_t n) {
    if (n == 0UL) {
        return NULL_FACTOR;
    }

    if (n < 4UL) {
        return std::make_tuple(n, 1UL);
    }

    if (n % 2 == 0UL) {
        return std::make_tuple(2UL, n / 2UL);
    }

    const auto root = sqrt(n);
    const auto sz = odd_primes.size();

    for (auto i = size_t(0); i <= root && i < sz; i++) {
        const auto p = odd_primes[i];

        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    }

    auto p = odd_primes.back();

    do {
        grow();

        if (odd_primes.back() == p) {
            continue;
        }

        p = odd_primes.back();

        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    } while (index <= root);

    return std::make_tuple(n, 1UL);
}

std::tuple<uint64_t, uint64_t> factor(uint64_t n) {
    return sieve{}.factor(n);
}
}
