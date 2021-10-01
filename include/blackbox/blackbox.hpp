#pragma once
/**
 * @copyright 2021 YelloSoft
 */

#include <cstdint>
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &o, __uint128_t x);

namespace blackbox {
__uint128_t stoulll(const std::string &str, std::size_t *pos = nullptr, int base = 10);

struct sieve {
    std::vector<__uint128_t> odd_primes{};

    __uint128_t index = 1;

    void grow();

    __uint128_t factor(__uint128_t n);
};
}
