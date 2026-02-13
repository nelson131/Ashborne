#pragma once

#include <vector>

#include "../utils/error_handler.hpp"
#include "scene.hpp"

class SceneManager {
   public:
    SceneManager();

    Scene* create_scene(std::string name);

    Scene* find_by(size_t id);
    Scene* find_by(std::string name);

   private:
    size_t get_unique();

    std::vector<Scene> holder;
};

extern SceneManager scene_manager;
