#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

#include "blackbox/blackbox.hpp"

static void panic(const std::string &label, const std::string &message) {
    std::cerr << label << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

static void test_algorithm(
    const std::string &label,
    const std::function<std::optional<std::tuple<uint64_t, uint64_t>>(uint64_t)> &a
) {
    for (auto n = 0UL; n < 4; n++) {
        if (a(n) != std::nullopt) { panic(label, "expected base case nullopt"); }
    }

    if (a(4UL) != std::make_tuple(2UL, 2UL)) { panic(label, "expected 4 -> (2, 2)"); }
    if (a(5UL) != std::nullopt) { panic(label, "expected 5 -> nullopt"); }
    if (a(6UL) != std::make_tuple(2UL, 3UL)) { panic(label, "expected 6 -> (2, 3)"); }
    if (a(7UL) != std::nullopt) { panic(label, "expected 7 -> nullopt"); }
    if (a(8UL) != std::make_tuple(2UL, 4UL)) { panic(label, "expected 8 -> (2, 4)"); }
}

int main() {
    test_algorithm("bruteforce", blackbox::factor_bruteforce);
    test_algorithm("sieve", blackbox::factor_sieve);
    test_algorithm("default", blackbox::factor);
    return EXIT_SUCCESS;
}
