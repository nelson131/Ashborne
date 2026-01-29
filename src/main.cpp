#include <iostream>
#include <memory>
#include <string>

#include "ashborne.hpp"
#include "utils/config.hpp"
#include "utils/log.hpp"

int main() {
    std::unique_ptr<Ashborne> ashborne = std::make_unique<Ashborne>();

    std::string name = config.get<std::string>("general", "name");
    std::string version = config.get<std::string>("general", "version");
    size_t      width = config.get<size_t>("general", "window-width");
    size_t      height = config.get<size_t>("general", "window-height");

    if (!ashborne->init(name.c_str(), width, height)) return 0;
    clog(INFO, name);
    clog(INFO, version);

    while (ashborne->is_running()) {
        ashborne->handle();
        ashborne->update();
        ashborne->render();
    }
    ashborne->quit();

    return 0;
}
