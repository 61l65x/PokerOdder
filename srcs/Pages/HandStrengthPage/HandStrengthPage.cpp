#include "HandStrengthPage.hpp"
#include <GLFW/glfw3.h>

HandStrengthPage::HandStrengthPage()
: _num_players(2), _cards_on_board(5), _top_pct(100), _iters(10000) {}

HandStrengthPage::~HandStrengthPage() = default;

void HandStrengthPage::show()
{
    int display_w, display_h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)display_w, (float)display_h));

    ImGui::Begin("Hand Strength Simulation", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::InputInt("Number of Players", &_num_players);
    ImGui::InputInt("Cards on Board", &_cards_on_board);
    ImGui::InputInt("Top % Highlighted", &_top_pct);
    ImGui::InputInt("Iterations per Hand", &_iters);

    if (ImGui::Button("Run Simulation")) {
        char num_players_str[10];
        char cards_on_board_str[10];
        char top_pct_str[10];
        char iters_str[10];

        snprintf(num_players_str, 10, "%d", _num_players);
        snprintf(cards_on_board_str, 10, "%d", _cards_on_board);
        snprintf(top_pct_str, 10, "%d", _top_pct);
        snprintf(iters_str, 10, "%d", _iters);

        const char *argv[] = { "", num_players_str, cards_on_board_str, top_pct_str, iters_str };
        _simulation_result = hand_strength_sim(5, (char**)argv);
    }

    ImGui::Text("Simulation Result:");
    ImGui::Separator();
    if (_simulation_result.empty())
        ImGui::TextWrapped("Please run the simulation to see the result.");
    else
    {
        for (const auto& line : _simulation_result)
            ImGui::TextColored(line.second, "%s", line.first.c_str());
    }
    ImGui::End();
}
