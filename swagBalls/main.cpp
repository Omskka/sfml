#include <iostream>
#include "game.h"

int main() {
    // Initialise random seed
    srand(time(nullptr));

    // Initialise game object
    game game;

    // Game loop
    while (game.running() && !game.getEndGame()) {
        game.update();
        game.render();
    }

    return 0;
}
