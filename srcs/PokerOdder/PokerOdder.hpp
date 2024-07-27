#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <vector>
#include <string>
#include "WindowPages.hpp"

class PokerOdder
{
public:
    PokerOdder();
    ~PokerOdder();

    bool initialize();
    void run();

private:
    WindowPages window_pages;
    void    show_simulation_window();

    GLFWwindow*                 _window;

    std::vector<std::pair<std::string, ImVec4>>    _simulation_result;
    int                         _num_players;
    int                         _cards_on_board;
    int                         _top_pct;
    int                         _iters;

    const char* glsl_version;
};
