#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "UI.h"
#include <vector>

struct Stash {
    std::vector<UI> player;
    std::vector<UI> world;

    void turn(std::vector<UI> storage, bool status, int id);
};

class UIManager {
    public:
    UIManager();
    enum class InitType {
        PLAYER,
        WORLD,
        ALL
    };

    void init(InitType type, const char* name);
    void update();
    void render();

    Stash stash;

    private:
};

extern UIManager uiManager;

#endif