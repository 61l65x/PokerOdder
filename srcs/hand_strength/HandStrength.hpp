#pragma once

#include <phevaluator/phevaluator.h>
#include <random>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cassert>

#define ITERS 100000

class HandStrength {
public:
    static int hand_strength_sim(int argc, char **argv);

private:
    static std::vector<int> _in;
    static std::unordered_map<int, std::string> rankMap;
};


