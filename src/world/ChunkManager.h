#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "Chunk.h"
#include "../scenes/SceneManager.h"
#include "../utils/Logger.h"
#include "../utils/Config.h"
#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include <string>

class ChunkManager {
    public:
    ChunkManager();

    void init(SDL_Renderer* renderer);

    void loadSceneByName(const char* name);
    void loadSceneById(size_t id);
    void loadChunksFromFile(Scene* scene);

    private:
    SDL_Renderer* renderer = nullptr;

    std::unordered_map<size_t, std::unique_ptr<Chunk>> stash;
};

#endif