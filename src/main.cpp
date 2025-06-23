#include <iostream>
#include <SDL.h>
#include "Ashborne.h"
#include "utils/Config.h"

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 840

Ashborne *ashborne = nullptr;
Config *config = nullptr;

int main(int, char**){
    ashborne = new Ashborne();

    config->config_init();
    std::cout << config->config_parse("game_info", "version") << std::endl;
    ashborne->game_init("Ashborne", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    while(ashborne->isRunning()){
        ashborne->eventManager();
        ashborne->update();
        ashborne->render();
    }

    ashborne->exit();

    return 0;
}
