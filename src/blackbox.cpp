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
        return std::make_tuple(0UL, 0UL);
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
        return std::make_tuple(0UL, 0UL);
    }

    if (n < 4UL) {
        return std::make_tuple(n, 1UL);
    }

    if (n % 2UL == 0) {
        return std::make_tuple(2UL, n / 2UL);
    }

    const auto root = sqrt(n);

    for (auto p = 3UL; p < root; p += 2) {
        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    }

    return std::make_tuple(n, 1UL);
}

void sieve::grow() {
    index += 2;

    bool prime = true;

    const auto root = sqrt(index);

    for (const auto p : odd_primes) {
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
        return std::make_tuple(0UL, 0UL);
    }

    if (n < 4UL) {
        return std::make_tuple(n, 1UL);
    }

    if (n % 2 == 0UL) {
        return std::make_tuple(2UL, n / 2UL);
    }

    const auto root = sqrt(n);

    for (const auto p : odd_primes) {
        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }

        if (p > root) {
            break;
        }
    }

    auto p = 0UL;

    do {
        grow();

        if (odd_primes.back() == p) {
            continue;
        }

        p = odd_primes.back();

        if (n % p == 0UL) {
            return std::make_tuple(p, n / p);
        }
    } while (index < root);

    return std::make_tuple(n, 1UL);
}

std::tuple<uint64_t, uint64_t> factor(uint64_t n) {
    return sieve{}.factor(n);
}
}
