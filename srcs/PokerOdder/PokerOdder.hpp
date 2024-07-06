#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>


int hand_strength_sim(int argc, char **argv);

class PokerOdder
{
public:
    PokerOdder();
    ~PokerOdder();

    bool initialize();
    void run();

private:
    void    show_simulation_window();

    GLFWwindow*    _window;
    int            _num_players;
    int            _cards_on_board;
    int            _top_pct;
    int            _iters;

    const char* glsl_version;
};
