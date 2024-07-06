
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <phevaluator/phevaluator.h>
#include <random>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cassert>

// Global variables for GUI input
int num_players = 2;
int cards_on_board = 5;
int top_pct = 100;
int iters = 1000000;

int hand_strength_sim(int argc, char **argv);

void show_simulation_window()
{
    int display_w, display_h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)display_w, (float)display_h));
    ImGui::Begin("Hand Strength Simulation", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::InputInt("Number of Players", &num_players);
    ImGui::InputInt("Cards on Board", &cards_on_board);
    ImGui::InputInt("Top % Highlighted", &top_pct);
    ImGui::InputInt("Iterations per Hand", &iters);

    if (ImGui::Button("Run Simulation")) {
        // Prepare arguments
        char num_players_str[10];
        char cards_on_board_str[10];
        char top_pct_str[10];
        char iters_str[10];

        snprintf(num_players_str, 10, "%d", num_players);
        snprintf(cards_on_board_str, 10, "%d", cards_on_board);
        snprintf(top_pct_str, 10, "%d", top_pct);
        snprintf(iters_str, 10, "%d", iters);

        const char *argv[] = { "", num_players_str, cards_on_board_str, top_pct_str, iters_str };
        hand_strength_sim(5, (char**)argv);
    }

    ImGui::End();
}

