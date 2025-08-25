#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <set>
#include <string>

enum class AnimType {
    IDLE_UP,
    IDLE_DOWN,
    IDLE_LEFT,
    IDLE_RIGHT,
    RUNY
};

struct AnimSet {
    AnimType type;
    SDL_Texture* texture;
    std::string path;
    int cells;
    bool isFlipped;

    bool operator<(const AnimSet& other) const{
        return type < other.type;
    }
};

class Animation {

    public:
    Animation();

    void fps(int fps);

    std::set<AnimSet>& getKeeper();
    void setup(std::string name);
    void play(SDL_Rect &srcRect, SDL_Texture*& t, SDL_RendererFlip& flip);

    AnimType getActive();
    void setActive(AnimType anim);

    AnimType toTypeFrom(std::string key);
    
    private:
    AnimType active;
    AnimType lastAnim;

    int currentFrame;
    int frameTime;
    Uint32 lastFrameTime;
    std::set<AnimSet> keeper;

    const AnimSet& findSetBy(AnimType& t) const;
};

#endif