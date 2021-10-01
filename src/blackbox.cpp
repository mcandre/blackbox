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
    if (x == __uint128_t(0)) {
        return o << '0';
    }

    std::vector<char> digits{};

    while (x > __uint128_t(0)) {
        digits.push_back('0' + char(x % __uint128_t(10)));
        x /= __uint128_t(10);
    }

    std::reverse(digits.begin(), digits.end());

    for (const auto digit : digits) {
        o << digit;
    }

    return o;
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
    auto x = __uint128_t(0);
    const auto sz = str.size();
    const auto sz_1 = sz - size_t(1);

    for (auto i = size_t(0); i < sz_1; i++) {
        x += std::stoi(str.substr(i, 1), pos, base);
        x *= __uint128_t(10);
    }

    x += std::stoi(str.substr(sz_1, 1), pos, base);
    return x;
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
    const auto root = sqrt(n);

    if (n % __uint128_t(2) == __uint128_t(0)) {
        return std::set<__uint128_t>{ __uint128_t(2), n / __uint128_t(2) };
    }

    for (const auto p : odd_primes) {
        if (n % p == __uint128_t(0)) {
            return std::set<__uint128_t>{ p, n / p };
        }
    }

    auto p = __uint128_t(0);

    while (index <= root) {
        grow();
        p = odd_primes.back();

        if (n % p == __uint128_t(0)) {
            return std::set<__uint128_t>{ p, n / p };
        }
    }

    return std::set<__uint128_t>{};
}
}
