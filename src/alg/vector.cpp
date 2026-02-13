#include "vector.hpp"

Vector::Vector() : x(0), y(0) {}

Vector::Vector(float x, float y) : x(x), y(y) {}

Vector& Vector::add(const Vector& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector& Vector::subtract(const Vector& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector& Vector::multiply(const Vector& v) {
    this->x *= x;
    this->y *= y;
    return *this;
}

Vector& Vector::divide(const Vector& v) {
    if (v.x == 0 || v.y == 0) {
        raise_error(ERR_DIVIDE_ON_ZERO, v.x, " | ", v.y);
    } else {
        this->x /= x;
        this->y /= y;
    }
    return *this;
}

Vector& operator+(Vector& v1, const Vector& v2) { return v1.add(v2); }

Vector& operator-(Vector& v1, const Vector& v2) { return v1.subtract(v2); }

Vector& operator*(Vector& v1, const Vector& v2) { return v1.multiply(v2); }

Vector& operator/(Vector& v1, const Vector& v2) { return v1.divide(v2); }

const float Vector::length() const { return sqrt(x * x + y * y); }

const float Vector::get_length(const Vector& v) const {
    return sqrt(v.x * v.x + v.y * v.y);
}

const float Vector::distance(float x, float y) const {
    float dx = x - this->x;
    float dy = y - this->y;
    return sqrt(dx * dx + dy * dy);
}

const float Vector::distance(const Vector& v) const {
    float dx = v.x - this->x;
    float dy = v.y - this->y;
    return sqrt(dx * dx + dy * dy);
}

Error Vector::normalize() {
    float length = this->length();
    if (length != 0) {
        this->x /= length;
        this->y /= length;
    } else {
        return ERR_NULL_VECTOR;
    }

    return NONE;
}

Vector Vector::get_normalized() const {
    float length = this->length();
    if (length != 0) {
        return Vector(this->x / length, this->y / length);
    }
    raise_error(ERR_NULL_VECTOR, this->x, " | ", this->y);
    return Vector();
}

const float Vector::dot(const Vector& v) const {
    return this->x * v.x + this->y * v.y;
}

bool Vector::is_equal(const Vector& v) const {
    return this->x == v.x && this->y == v.y;
}

Vector Vector::clone() const { return Vector(this->x, this->y); }
