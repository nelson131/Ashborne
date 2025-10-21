#ifndef UI_H
#define UI_H

#include "UIModule.h"
#include "../alg/Vector.h"
#include <SDL2/SDL.h>
#include <string>
#include <memory>

struct ContainerUI {
    std::vector<std::unique_ptr<UIModule::Base>> modules;
};

class UI {
    public:
    UI();
    void init();
    void update();
    void render();

    template<typename T, typename... Args>
    T* addModule(Args&&... args){
        static_assert(std::is_base_of<UIModule::Base, T>::value, "Object must by from UIModule");
        auto module = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = module.get();
        container.modules.push_back(std::move(module));
        return raw;
    }

    ContainerUI& getContainer();

    std::string title = "";
    int id = -1;
    bool locked = true;
    bool visible = true;

    Vector position = {0, 0};

    private:
    ContainerUI container;

    SDL_Rect destRect = {0, 0, 0, 0};
};

#endif