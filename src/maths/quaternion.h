#pragma once

#include <glm/glm.hpp>
#include <string>





// Class Quaternion : Permet de modéliser un quaternion.
class Quaternion {

public :

    // Constructeurs, destructeur.
    Quaternion();
    Quaternion(glm::vec3 axis, double angle);
    Quaternion(double x, double y, double z, double w);
    ~Quaternion();

    // Surcharge des opérateurs arithmétiques.
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator-() const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(double v) const;
    Quaternion operator/(double v) const;

    // Surcharge des opérateurs d'affectation.
    Quaternion& operator=(const Quaternion& q);
    Quaternion& operator+=(const Quaternion& q);
    Quaternion& operator-=(const Quaternion& q);
    Quaternion& operator*=(const Quaternion& q);
    Quaternion& operator*=(const double v);
    Quaternion& operator/=(const double v);

    // Rotation de vecteur.
    void rotation(glm::vec3& v) const;

    // Normalisation du quaternion.
    Quaternion& normalize();

    // Getters.
    double norm() const;
    Quaternion conj() const;
    Quaternion inv() const;
    std::string str() const;
    
    // Coordonnées.
    double x;
    double y;
    double z;
    double w;

};





// Surcharge de l'opérateur d'égalité.
bool operator==(Quaternion const& q1, Quaternion const& q2);



// Opérateurs de produit par un scalaire à gauche.
Quaternion operator*(double s, const Quaternion& q);
Quaternion operator/(double s, const Quaternion& q);
