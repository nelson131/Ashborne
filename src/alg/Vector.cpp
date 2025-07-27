#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Vector.h"
#include "../utils/Logger.h"

Vector::Vector()
    : x(x), y(y)
{}

Vector::Vector(float x, float y){
    this->x = x;
    this->y = y;
}

Vector& Vector::add(const Vector& v){
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector& Vector::add(float x, float y){
    this->x += x;
    this->y += y;
    return *this;
}

Vector Vector::getAdded(const Vector& v){
    return Vector(this->x + v.x, this->y + v.y);
}

Vector& Vector::subtract(const Vector& v){
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector& Vector::subtract(float x, float y){
    this->x -= x;
    this->y -= y;
    return *this;
}

Vector Vector::getSubtracted(const Vector& v){
    return Vector(this->x - v.x, this->y - v.y);
}

Vector& Vector::divide(const Vector& v){
    this->x /= v.x;
    this->y /= v.y;
    return *this;
}

Vector& Vector::divide(float x, float y){
    this->x /= x;
    this->y /= y;
    return *this;
}

Vector Vector::getDivided(const Vector& v){
    return Vector(this->x / v.x, this->y / v.y);
}

Vector& Vector::multiply(const Vector& v){
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector& Vector::multiply(float x, float y){
    this->x *= x;
    this->y *= y;
    return *this;
}

Vector Vector::getMultiplied(const Vector& v){
    return Vector(this->x * v.x, this->y * v.y);
}

Vector& operator + (Vector& v1, const Vector& v2){
    return v1.add(v2);
}

Vector& operator - (Vector& v1, const Vector& v2){
    return v1.subtract(v2);
}

Vector& operator / (Vector& v1, const Vector& v2){
    return v1.divide(v2);
}

Vector& operator * (Vector& v1, const Vector& v2){
    return v1.multiply(v2);
}

Vector operator * (Vector& v, float f){
    return Vector(v.x * f, v.y * f);
}

Vector& Vector::set(float x, float y){
    this->x = x;
    this->y = y;
    return *this;
}

float Vector::getLength(){
    return sqrt(this->x * this->x + this->y * this->y);
}

float Vector::getDistance(float x, float y){
    x -= this->x;
    y -= this->y;
    return sqrt(x * x + y * y);
}

float Vector::getDistance(const Vector& v) const{
    float x = v.x - this->x;
    float y = v.y - this->y;
    return sqrt(x * x + y * y);
}

float Vector::getAngle(){
    return atan2(this->y, this->x);
}

float Vector::getAngle(const Vector& v) const{
    return atan2(v.y, v.x);
}

void Vector::normalize(){
    float l = getLength();
    if(l != 0){
        this->x /= l;
        this->y /= l;
    } else {
        Logger::print(Logger::WARNING, "Couldnt normalize cause length of vector is zero");
    }
}

Vector Vector::getNormalized(){
    float l = getLength();
    if(l != 0){
        return Vector(this->x / l, this->y / l);
    }
    Logger::print(Logger::WARNING, "Couldnt normalize cause length of vector is zero");
    return *this;
}

float Vector::dot(const Vector& v){
    return (this->x * v.x + this->y * v.y);
}

float Vector::dot(float x, float y){
    return (this->x * x + this->y * y);
}

float Vector::dot(const Vector& v1, const Vector& v2){
    return (v1.x * v2.x + v1.y * v2.y);
}

void Vector::rotate(float angle){
    float cos = std::cos(angle);
    float sin = std::sin(angle);
    this->x = this->x * cos - this->y * sin;
    this->y = this->x * sin + this->y * cos;
}

Vector Vector::getRotated(float angle){
    float cos = std::cos(angle);
    float sin = std::sin(angle);
    return Vector(this->x * cos - this->y * sin, this->x * sin + this->y * cos);
}


Vector Vector::clone(const Vector& v){
    return Vector(this->x, this->y);
}

bool Vector::equals(const Vector& v){
    return this->x == v.x && this->y == v.y;
}

float Vector::sin(float& f){
    return asin(f);
}

float Vector::dsin(float& f){
    return asin(f) *(180.0 / M_PI);
}

float Vector::cos(float& f){
    return acos(f);
}

float Vector::dcos(float& f){
    return acos(f) * (180.0 / M_PI);
}
