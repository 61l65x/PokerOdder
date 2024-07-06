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

int hand_strength_sim(int argc, char **argv);
void show_simulation_window();

// Global variables for GUI input
int num_players = 2;
int cards_on_board = 5;
int top_pct = 100;
int iters = 1000000;

int main(int argc, char **argv) {
    // Setup GLFW window
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hand Strength Simulation", NULL, NULL);
    if (window == NULL)
        return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show simulation window
        show_simulation_window();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

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

