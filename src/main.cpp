#include <iostream>
#include <memory>
#include <string>

#include "ashborne.hpp"
#include "utils/config.hpp"

int main() {
    std::unique_ptr<Ashborne> ashborne = std::make_unique<Ashborne>();

    std::string name = config.get<std::string>("general", "name");
    size_t      width = config.get<size_t>("general", "window-width");
    size_t      height = config.get<size_t>("general", "window-height");

    if (!ashborne->init(name.c_str(), width, height)) return 0;
    while (ashborne->is_running()) {
        ashborne->handle();
        ashborne->update();
        ashborne.render();
    }
    ashborne->quit();

    return 0;
}
