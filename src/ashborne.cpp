#include "ashborne.hpp"

#include "utils/error_handler.hpp"

Ashborne::Ashborne() : window(nullptr), renderer(nullptr), run(false) {}

Error Ashborne::init(const char* title, size_t width, size_t height) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVENTS);

    window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        return ERR_NULLPTR_OBJECT;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        return ERR_NULLPTR_OBJECT;
    }

    run = true;
    return NONE;
}

void Ashborne::handle() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                run = false;
                break;
            default:
                break;
        }
    }
}

void Ashborne::update() {}

void Ashborne::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Ashborne::quit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

const bool& Ashborne::is_running() const { return run; }
