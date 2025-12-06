#include "Game.h"

int main (int argc, char *argv[]) {
    Game gameObject;

    if(gameObject.Initialize() == true) {
        gameObject.Run();
    }

    gameObject.Shutdown();

    return 0;
}
