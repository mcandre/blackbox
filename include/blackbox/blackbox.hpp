#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include <tuple>

std::ostream &operator<<(std::ostream &o, const std::tuple<uint64_t, uint64_t> &n);

namespace blackbox {
std::optional<std::tuple<uint64_t, uint64_t>> factor_bruteforce(uint64_t n);

std::optional<std::tuple<uint64_t, uint64_t>> factor(uint64_t n);
}
