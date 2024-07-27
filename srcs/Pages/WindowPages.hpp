#pragma once

#include "HandStrengthPage.hpp"
#include <vector>

class WindowPages
{

private:
    std::vector<AWindowPage *> _pages;

public:
    WindowPages()
    {
        _pages.push_back(new HandStrengthPage());
    }

    ~WindowPages()
    {
        for (auto page : _pages)
            delete page;
    }

    void show_pages()
    {
        for (auto page : _pages)
            page->show();
    }
};
