#pragma once

// Dependencies : glm 
// ----------------------------------------------------------------------------
// Quaternions are hypercomplex numbers that provide a highly efficient and 
// stable way to represent rotations. Unlike matrix rotations, quaternion 
// rotations avoid issues like gimbal lock and require fewer computational 
// resources when chained, making them ideal for smooth, continuous rotations.
// This class supports standard algebraic operations (+, -, *, /) and 
// corresponding assignment operators, as well as operations for normalization,
// inversion, vector rotation, and norm measurement.

#include <string>
#include <glm/glm.hpp>



// Class Quaternion : Type to manipulate quaternions.
class Quaternion {
public :

    // Constructors, destructor.
    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(glm::vec3 axis, float angle);
    Quaternion(float x, float y, float z, float w);
    ~Quaternion();

    // Arithmetical operations overload.
    friend Quaternion operator+(Quaternion q1, const Quaternion &q2);
    friend Quaternion operator-(Quaternion q1, const Quaternion &q2);
    friend Quaternion operator-(Quaternion q);
    friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2);
    friend Quaternion operator*(Quaternion q, float v);
    friend Quaternion operator/(Quaternion q, float v);
    friend Quaternion operator*(float v, Quaternion q);
    friend Quaternion operator/(float v, Quaternion q);

    // Affectation operations overload.
    Quaternion &operator=(const Quaternion &q);
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);
    Quaternion &operator*=(const Quaternion &q);
    Quaternion &operator*=(const float v);
    Quaternion &operator/=(const float v);

    // Vector rotation.
    void rotation(glm::vec3 &v) const;

    // Normalization of the quaternion.
    Quaternion &normalize();

    // Getters.
    float norm() const;
    Quaternion normalized() const;
    Quaternion conj() const;
    Quaternion inv() const;
    std::string to_string() const;
    
    // Coordinates.
    float x;
    float y;
    float z;
    float w;

};
