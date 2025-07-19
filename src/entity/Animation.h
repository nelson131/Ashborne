#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <map>

class Animation {

    public:
    Animation();

    enum class Type {
        IDLE,
        RUNX,
        RUNY
    };

    void fps(int fps);

    std::map<Type, int>& getKeeper();
    void add(Type animType, int cells);
    void remove(Type animType);

    void play(Animation::Type animType, SDL_Rect &srcRect);
    
    private:
    int currentFrame;
    int frameTime;
    Uint32 lastFrameTime;
    std::map<Type, int> keeper;
};

#endif