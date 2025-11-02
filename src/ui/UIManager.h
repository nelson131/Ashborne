#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "UI.h"
#include <vector>

struct Stash {
    enum class InitType {
        PLAYER,
        WORLD,
        ALL
    };

    enum class PositionType {
        RIGHT,
        LEFT,
        TOP,
        DOWN,
        CENTER
    };

    std::vector<UI> player;
    std::vector<UI> world;

    void turn(std::vector<UI> storage, bool status, int id);
    PositionType toPosTypeFrom(std::string& value);
};

class UIManager {
    public:
    UIManager();

    void init(Stash::InitType type, const char* name);
    void update();
    void render();

    void ikuyoPosition(Vector& position, Stash::PositionType type);

    Stash stash;

    private:
};

extern UIManager uiManager;

#endif