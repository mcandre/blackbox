#include <cassert>
#include <cstdint>
#include <functional>
#include <optional>

#include "blackbox/blackbox.hpp"

static void test_algorithm(const std::function<std::optional<std::tuple<uint64_t, uint64_t>>(uint64_t)> &a) {
    for (auto n = 0UL; n < 4; n++) {
        assert(a(n) == std::nullopt);
    }

    assert(a(4UL) == std::make_tuple(2UL, 2UL));
    assert(a(6UL) == std::make_tuple(2UL, 3UL));
}

int main() {
    for (const auto a : std::vector{blackbox::factor_bruteforce, blackbox::factor_sieve, blackbox::factor}) {
        test_algorithm(a);
    }

    return EXIT_SUCCESS;
}
