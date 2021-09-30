/**
 * @copyright 2021 YelloSoft
 */

#include <algorithm>
#include <cstdint>
#include <ctgmath>
#include <iostream>
#include <set>
#include <vector>

#include "blackbox/blackbox.hpp"

std::ostream &operator<<(std::ostream &o, const std::set<uint64_t> &n) {
    o << "{ ";

    const auto sz = n.size();
    auto it = n.begin();

    for (auto i = size_t(0); i < sz; i++) {
        o << *it;

        if (sz > 1 && i < sz - 1) {
            o << ", ";
        }

        std::advance(it, 1);
    }

    return o << " }";
}

namespace blackbox {
std::set<uint64_t> factor_bruteforce(uint64_t n) {
    if (n < 2UL) {
        return std::set<uint64_t>{ n };
    }

    if (n < 4UL) {
        return std::set<uint64_t>{ 1UL, n };
    }

    for (auto p = 2UL; p < n; p++) {
        if (n % p == 0UL) {
            return std::set<uint64_t>{ p, n / p };
        }
    }

    return std::set<uint64_t>{ 1UL, n };
}

std::set<uint64_t> factor_odd_linear(uint64_t n) {
    if (n < 2UL) {
        return std::set<uint64_t>{ n };
    }

    if (n < 4UL) {
        return std::set<uint64_t>{ 1UL, n };
    }

    if (n % 2UL == 0) {
        return std::set<uint64_t>{ 2UL, n / 2UL };
    }

    const auto root = sqrt(n);

    for (auto p = 3UL; p <= root; p += 2) {
        if (n % p == 0UL) {
            return std::set<uint64_t>{ p, n / p };
        }
    }

    return std::set<uint64_t>{ 1UL, n };
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

std::set<uint64_t> sieve::factor(uint64_t n) {
    if (n < 2UL) {
        return std::set<uint64_t>{ n };
    }

    if (n < 4UL) {
        return std::set<uint64_t>{ 1UL, n };
    }

    if (n % 2 == 0UL) {
        return std::set<uint64_t>{ 2UL, n / 2UL };
    }

    const auto root = sqrt(n);

    for (const auto p : odd_primes) {
        if (n % p == 0UL) {
            return std::set<uint64_t>{ p, n / p };
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
            return std::set<uint64_t>{ p, n / p };
        }
    } while (index < root);

    return std::set<uint64_t>{ 1UL, n };
}

std::set<uint64_t> factor(uint64_t n) {
    return sieve{}.factor(n);
}
}
