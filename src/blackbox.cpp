#include <cstdint>
#include <iostream>
#include <optional>
#include <tuple>

#include "blackbox/blackbox.hpp"

std::ostream &operator<<(std::ostream &o, const std::tuple<uint64_t, uint64_t> &n) {
    const auto [p, q] = n;
    return o << "(" << p << ", " << q << ")";
}

namespace blackbox {
std::optional<std::tuple<uint64_t, uint64_t>> factor_bruteforce(uint64_t n) {
    if (n == 0UL) {
        return std::nullopt;
    }

    // ...

    return std::optional(std::make_tuple(1UL, n));
}

std::optional<std::tuple<uint64_t, uint64_t>> factor(uint64_t n) {
    return factor_bruteforce(n);
}
}
