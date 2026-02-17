#pragma once
#include <random>
class RNG {
public:

    static float randomFloat(float min, float max) {
        std::uniform_real_distribution<float> dist (min, max);
        return dist(engine());
    }

    static int randomInt(int min, int max) {
        std::uniform_int_distribution<int> dist (min, max);
        return dist(engine());
    }


private:

    static std::mt19937& engine() {
        static thread_local std::mt19937 eng{ std::random_device{}()};
        return eng;
    }

};