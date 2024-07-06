#include "PokerOdder.hpp"

int main(int argc, char **argv) 

{
    PokerOdder app;
    if (!app.initialize())
    {
        return -1;
    }
    app.run();
    return 0;
}
