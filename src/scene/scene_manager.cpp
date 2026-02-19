#include "scene_manager.hpp"

#include <iostream>

SceneManager scene_manager;

SceneManager::SceneManager() : renderer(nullptr) {}

Error SceneManager::init(SDL_Renderer* renderer) { this->renderer = renderer; }

Scene* SceneManager::create_scene(std::string name) {
    Scene scene;
    scene.name = name;
    scene.id = get_unique();

    holder.push_back(scene);
    return &holder[holder.size() - 1];
}

Scene* SceneManager::find_by(size_t id) {
    for (size_t i = 0; i < holder.size(); i++) {
        if (holder[i].id == id) {
            return &holder[i];
        }
    }
    raise_error(ERR_SOMETHING_NOT_FOUND, "scene by id: ", id);
    return nullptr;
}

Scene* SceneManager::find_by(std::string name) {
    for (size_t i = 0; i < holder.size(); i++) {
        if (holder[i].name == name) {
            return &holder[i];
        }
    }
    raise_error(ERR_SOMETHING_NOT_FOUND, "scene by name: ", name);
    return nullptr;
}

size_t SceneManager::get_unique() {
    size_t unique = 0;
    for (size_t i = 0; i < holder.size(); i++) {
        if (holder[i].id > unique) {
            unique = holder[i].id;
        }
    }

    return unique + 1;
}
