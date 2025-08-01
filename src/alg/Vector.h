#ifndef VECTOR_H
#define VECTOR_H

#include "../utils/Logger.h"

class Vector {
    public:
    float x;
    float y;
    
    Vector();
    Vector(float x, float y);

    Vector& add(const Vector& v);
    Vector& add(float x, float y);
    Vector getAdded(const Vector& v);

    Vector& subtract(const Vector& v);
    Vector& subtract(float x, float y);
    Vector getSubtracted(const Vector& v);

    Vector& divide(const Vector& v);
    Vector& divide(float x, float y);
    Vector getDivided(const Vector& v);

    Vector& multiply(const Vector& v);
    Vector& multiply(float x, float y);
    Vector getMultiplied(const Vector& v);
    

    friend Vector& operator + (Vector& v1, const  Vector& v2);
    friend Vector& operator - (Vector& v1, const Vector& v2);
    friend Vector& operator / (Vector& v1, const Vector& v2);
    friend Vector& operator * (Vector& v1, const Vector& v2);
    friend Vector operator * (Vector& v, float f);

    Vector& set(float x, float y);

    float getLength();

    float getDistance(float x, float y);
    float getDistance(const Vector& v) const;

    float getAngle();
    float getAngle(const Vector& v) const;

    void normalize();
    Vector getNormalized();

    float dot(const Vector& v);
    float dot(float x, float y);
    float dot(const Vector& v1, const Vector& v2);

    void rotate(float angle);
    Vector getRotated(float angle);
    
    Vector clone(const Vector& v);

    bool equals(const Vector& v);

    float sin(float& f);
    float dsin(float& f);
    float cos(float& f);
    float dcos(float& f);
};


#endif