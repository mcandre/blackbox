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
    const auto sz_1 = sz - 1;
    auto it = n.begin();

    for (auto i = size_t(0); i < sz; i++) {
        o << *it;

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

std::set<uint64_t> sieve::factor(uint64_t n) {
    if (n == 0UL) {
        return std::set<uint64_t>{};
    }

    if (n == 1UL) {
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
        p = odd_primes.back();

        if (n % p == 0UL) {
            return std::set<uint64_t>{ p, n / p };
        }
    } while (index < root);

    return std::set<uint64_t>{ 1UL, n };
}
}
