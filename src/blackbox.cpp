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

std::ostream &operator<<(std::ostream &o, __uint128_t x) {
    const auto upper = uint64_t(x >> __uint128_t(64));

    if (upper > 0ULL) {
        o << upper;
    }

    return o << uint64_t(x);
}

std::ostream &operator<<(std::ostream &o, const std::set<__uint128_t> &n) {
    o << "{ ";

    const auto sz = n.size();
    const auto sz_1 = sz - 1;
    auto it = n.begin();

    for (auto i = size_t(0); i < sz; i++) {
        o << *it;

        if (sz > size_t(1) && i < sz_1) {
            o << ", ";
        }

        std::advance(it, 1);
    }

    return o << " }";
}

namespace blackbox {
__uint128_t stoulll(const std::string &str, size_t *pos, int base) {
        const auto lower_len = std::min(str.size(), size_t(20));
        const auto upper_len = std::min(str.size() - lower_len, size_t(20));
        const auto upper_s = str.substr(0, upper_len);
        const auto lower_s = str.substr(upper_len);
        auto upper = 0ULL;

        if (upper_len > size_t(0)) {
            upper = std::stoul(upper_s, pos, base);
        }

        const auto lower = std::stoul(lower_s, pos, base);
        return (__uint128_t(upper) << __uint128_t(64)) + __uint128_t(lower);
}

void sieve::grow() {
    bool prime = false;
    auto root = __uint128_t(0);

    while (true) {
        index += __uint128_t(2);
        root = sqrt(index);
        prime = true;

        for (const auto p : odd_primes) {
            if (index % p == __uint128_t(0)) {
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
        return std::set<__uint128_t>{ __uint128_t(1), n };
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
