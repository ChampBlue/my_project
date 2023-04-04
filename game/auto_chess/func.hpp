#include "class.hpp"

std::array<short, 3> random_unit() {
    std::array<short, 3> rand_unit = {0,0,0};

    for(int i = 0; i < 3; i++) {
        std::random_device seed_value;
        std::mt19937 gen(seed_value());
        std::uniform_int_distribution<int> rand(1, 7);
        short temp_unit = rand(gen);
        rand_unit[i] = temp_unit;
    }

    return rand_unit;
}

