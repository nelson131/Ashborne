#pragma once

#include <math.h>

#include "../utils/error_handler.hpp"

class Vector {
   public:
    Vector();
    Vector(float x, float y);
    float x;
    float y;

    Vector& add(const Vector& v);
    Vector& subtract(const Vector& v);
    Vector& multiply(const Vector& v);
    Vector& divide(const Vector& v);

    friend Vector& operator+(Vector& v1, const Vector& v2);
    friend Vector& operator-(Vector& v1, const Vector& v2);
    friend Vector& operator*(Vector& v1, const Vector& v2);
    friend Vector& operator/(Vector& v1, const Vector& v2);

    const float length() const;
    const float get_length(const Vector& v) const;

    const float distance(float x, float y) const;
    const float distance(const Vector& v) const;

    Error  normalize();
    Vector get_normalized() const;

    const float dot(const Vector& v) const;

    bool is_equal(const Vector& v) const;

    Vector clone() const;
};
