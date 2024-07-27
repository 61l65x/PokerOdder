#include "PokerOdder.hpp"
#include <iostream>

PokerOdder::PokerOdder()
{
    _window = nullptr;
    _num_players = 2;
    _cards_on_board = 5;
    _top_pct = 100;
    _iters = 10000;
    glsl_version = "#version 130";
}

PokerOdder::~PokerOdder()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool PokerOdder::initialize()
{
    // GLFW Init 
    if (!glfwInit()) return false;
    _window = glfwCreateWindow(1280, 720, "Hand Strength Simulation", NULL, NULL);
    if (_window == NULL) return false;
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1); 

    // ImGui Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void PokerOdder::run() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window_pages.show_pages();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }
}
