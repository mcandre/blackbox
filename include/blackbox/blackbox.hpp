#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>

std::ostream &operator<<(std::ostream &o, const std::tuple<uint64_t, uint64_t> &n);

namespace blackbox {
std::optional<std::tuple<uint64_t, uint64_t>> factor_bruteforce(uint64_t n);

struct sieve {
    std::vector<uint64_t> primes{ 2UL };

    uint64_t index = 2UL;

    void grow();
};

std::optional<std::tuple<uint64_t, uint64_t>> factor_sieve(uint64_t n);

std::optional<std::tuple<uint64_t, uint64_t>> factor(uint64_t n);
}
