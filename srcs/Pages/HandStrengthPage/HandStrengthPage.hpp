#pragma once 

#include <string>
#include <vector>
#include "imgui.h"
#include "AWindowPage.hpp"

std::vector<std::pair<std::string, ImVec4>> hand_strength_sim(int argc, char **argv);

class HandStrengthPage : public AWindowPage {
public:
    HandStrengthPage();
    ~HandStrengthPage();
    void show();

private:
    int _num_players;
    int _cards_on_board;
    int _top_pct;
    int _iters;
    std::vector<std::pair<std::string, ImVec4>> _simulation_result;
};