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

std::ostream &operator<<(std::ostream &o, const std::set<__uint128_t> &n) {
    o << "{ ";

    const auto sz = n.size();
    const auto sz_1 = sz - 1;
    auto it = n.begin();

    for (auto i = size_t(0); i < sz; i++) {
        const auto factor = *it;

        o << uint64_t(factor >> __uint128_t(64));
        o << uint64_t(factor);

        if (sz > 1 && i < sz_1) {
            o << ", ";
        }

        std::advance(it, 1);
    }

    return o << " }";
}

namespace blackbox {
void sieve::grow() {
    bool prime = false;
    auto root = 0UL;

    while (true) {
        index += 2;
        root = sqrt(index);
        prime = true;

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
            break;
        }
    }
}

std::set<__uint128_t> sieve::factor(__uint128_t n) {
    if (n == __uint128_t(0)) {
        return std::set<__uint128_t>{};
    }

    if (n == __uint128_t(1)) {
        return std::set<__uint128_t>{ n };
    }

    if (n < __uint128_t(4)) {
        return std::set<__uint128_t>{ 1UL, n };
    }

    if (n % __uint128_t(2) == __uint128_t(0)) {
        return std::set<__uint128_t>{ __uint128_t(2), n / __uint128_t(2) };
    }

    const auto root = sqrt(n);

    for (const auto p : odd_primes) {
        if (n % p == __uint128_t(0)) {
            return std::set<__uint128_t>{ p, n / p };
        }

        if (p > root) {
            break;
        }
    }

    auto p = __uint128_t(0);

    do {
        grow();
        p = odd_primes.back();

        if (n % p == __uint128_t(0)) {
            return std::set<__uint128_t>{ p, n / p };
        }
    } while (index < root);

    return std::set<__uint128_t>{ __uint128_t(1), n };
}
}
