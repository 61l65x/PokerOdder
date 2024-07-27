#include "PokerOdder.hpp"
#include "HandStrength.hpp"
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

void PokerOdder::run()
{
    while (!glfwWindowShouldClose(_window))
    {
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
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }
}

void PokerOdder::show_simulation_window() {
    static int simulation_runned = 0;
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)display_w, (float)display_h));
    ImGui::Begin("Hand Strength Simulation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::InputInt("Number of Players", &_num_players);
    ImGui::InputInt("Cards on Board", &_cards_on_board);
    ImGui::InputInt("Top % Highlighted", &_top_pct);
    ImGui::InputInt("Iterations per Hand", &_iters);

    if (ImGui::Button("Run Simulation")) {
        simulation_runned++;
        char num_players_str[10];
        char cards_on_board_str[10];
        char top_pct_str[10];
        char iters_str[10];

        snprintf(num_players_str, 10, "%d", _num_players);
        snprintf(cards_on_board_str, 10, "%d", _cards_on_board);
        snprintf(top_pct_str, 10, "%d", _top_pct);
        snprintf(iters_str, 10, "%d", _iters);

        const char *argv[] = { "", num_players_str, cards_on_board_str, top_pct_str, iters_str };
        this->_simulation_result = HandStrength::hand_strength_sim(5, (char**)argv);
    }

    ImGui::Text("Simulation Result:");
    ImGui::Separator();
    if (_simulation_result.empty()) {
        ImGui::TextWrapped("Please run the simulation to see the result.");
    } else {
        for (const auto& line : _simulation_result) {
            ImGui::TextWrapped("%s", line.c_str());
            std::cout << line << std::endl;
        }
    }

    ImGui::End();
}
