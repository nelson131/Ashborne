#include "UIModule.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace UIModule {

    // Base ->
    Base::Base(){}
    Base::~Base() = default;

    void Base::init(const Vector v, const Vector size){}
    void Base::update(Vector& relative){}
    void Base::render(){}

}