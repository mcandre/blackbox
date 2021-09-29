#include <cassert>
#include <cstdint>
#include <optional>

#include "blackbox/blackbox.hpp"

void test_bruteforce() {
    for (auto n = 0UL; n < 4; n++) {
        assert(blackbox::factor_bruteforce(n) == std::nullopt);
    }

    assert(blackbox::factor_bruteforce(6UL) == std::make_tuple(2UL, 3UL));
}

void test_sieve() {
    for (auto n = 0UL; n < 4; n++) {
        assert(blackbox::factor_sieve(n) == std::nullopt);
    }

    assert(blackbox::factor_sieve(6UL) == std::make_tuple(2UL, 3UL));
}

void test_default() {
    for (auto n = 0UL; n < 4; n++) {
        assert(blackbox::factor(n) == std::nullopt);
    }

    assert(blackbox::factor(6UL) == std::make_tuple(2UL, 3UL));
}

int main() {
    test_bruteforce();
    test_sieve();
    test_default();
    return EXIT_SUCCESS;
}
