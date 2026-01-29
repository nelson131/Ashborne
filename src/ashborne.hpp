#pragma once

#include "utils/error_handler.hpp"

class Ashborne {
   public:
    Ashborne();

    Error init(const char* name, size_t width, size_t height);

    void handle();
    void update();
    void render();

    void quit();

    const bool& is_running() const;

   private:
    bool run;
};
