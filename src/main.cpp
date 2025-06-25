#include <iostream>
#include <SDL.h>
#include "Ashborne.h"
#include <memory>
#include "utils/Config.h"

std::unique_ptr<Ashborne> ashborne;
std::unique_ptr<Config> config;

int main(int, char**){
    ashborne = std::make_unique<Ashborne>();
    config = std::make_unique<Config>();

    const float FPS = 60;
    const float frameDelay = 1000 / FPS;
    Uint32 frameStart;
    float frameTime;

    config->config_init();

    int WINDOW_WIDTH = config->config_parseInt("game_info", "width");
    int WINDOW_HEIGHT = config->config_parseInt("game_info", "height");

    std::cout << config->config_parse("game_info", "version") << std::endl;
    ashborne->game_init("Ashborne", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    while(ashborne->isRunning()){
        frameStart = SDL_GetTicks();

        ashborne->eventManager();
        ashborne->update();
        ashborne->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

    ashborne->exit();

    return 0;
}
