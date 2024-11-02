#include "quaternion.h"

#include <cmath>





// Constructeur.
Quaternion::Quaternion() {
    Quaternion(0,0,0,1);
}



// Constructeur.
Quaternion::Quaternion(glm::vec3 axis, double angle) {

    // Normalise l'axe et calcule le cos et sin de l'angle.
    axis = glm::normalize(axis);
    double s = std::sin(angle/2.0);
    double c = std::cos(angle/2.0);

    // En déduit les coordonnées du quaternion.
    this->x = s*axis.x;
    this->y = s*axis.y;
    this->z = s*axis.z;
    this->w = c;

}



// Constructeur.
Quaternion::Quaternion(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}



// Destructeur.
Quaternion::~Quaternion() {
}





// Somme de quaternions.
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}



// Différence de quaternions.
Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
}



// Opposé du quaternion.
Quaternion Quaternion::operator-() const {
    return Quaternion(-x, -y, -z, -w);
}



// Produit de quaternions.
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion (
        w*q.x + x*q.x + y*q.z - z*q.y,
        w*q.y - x*q.z + y*q.w + z*q.x,
        w*q.z + x*q.y - y*q.x + z*q.w,
        w*q.w + x*q.x + y*q.y + z*q.z
    );
}



// Produit par un scalaire à droite.
Quaternion Quaternion::operator*(double v) const {
    return Quaternion(x*v, y*v, z*v, w*v);
}



// Division par un scalaire à droite.
Quaternion Quaternion::operator/(double v) const {
    return Quaternion(x/v, y/v, z/v, w/v);
}





// Opérateur d'affectation.
Quaternion& Quaternion::operator=(const Quaternion& q) {
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    this->w = q.w;
    return *this;
}



// Opérateur d'affectation d'addition.
Quaternion& Quaternion::operator+=(const Quaternion& q) {
    this->x += q.x;
    this->y += q.y;
    this->z += q.z;
    this->w += q.w;
    return *this;
}



// Opérateur d'affectation de différence.
Quaternion& Quaternion::operator-=(const Quaternion& q) {
    this->x -= q.x;
    this->y -= q.y;
    this->z -= q.z;
    this->w -= q.w;
    return *this;
}



// Opérateur d'affectation de produit.
Quaternion& Quaternion::operator*=(const Quaternion& q) {
    Quaternion res = (*this) * q;
    (*this) = res;
    return *this;
}



// Opérateur d'affectation de produit par un scalaire.
Quaternion& Quaternion::operator*=(const double v) {
    this->x *= v;
    this->y *= v;
    this->z *= v;
    this->w *= v;
    return *this;
}



// Opérateur d'affectation de division par un scalaire.
Quaternion& Quaternion::operator/=(const double v) {
    this->x /= v;
    this->y /= v;
    this->z /= v;
    this->w /= v;
    return *this;
}





// Rotation de vecteur selon le quaternion.
void Quaternion::rotation(glm::vec3& v) const {
    glm::vec3 xyz = glm::vec3(x,y,z);
    glm::vec3 t = 2.0f*glm::cross(xyz, v);
    v += static_cast<float>(w)*t + glm::cross(xyz, t);
}





// Normalise le quaternion.
Quaternion& Quaternion::normalize() {
    return (*this) /= norm();
}





// Norme du quaternion.
double Quaternion::norm() const {
    return sqrt(x*x + y*y + z*z + w*w);
}



// Conjugué du quaternion.
Quaternion Quaternion::conj() const {
    return Quaternion(-x, -y, -z, w);
}



// Inverse du quaternion.
Quaternion Quaternion::inv() const {
    double n = norm();
    return conj() / (n*n);
}



// Renvoie un string représentant le quaternion.
std::string Quaternion::str() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) 
        + ", " + std::to_string(z) + ", " + std::to_string(w) + "]";
}





// Surcharge de l'opérateur d'égalité.
bool operator==(Quaternion const& q1, Quaternion const& q2) {
    return q1.w == q2.w && q1.x == q2.x && q1.y == q2.y && q1.z == q2.z;
}





// Produit par un scalaire à gauche.
Quaternion operator*(double s, const Quaternion& q) {
    return q*s;
}



// Division d'un scalaire par un quaternion.
Quaternion operator/(double s, const Quaternion& q) {
    return Quaternion(0,0,0,s) * q.inv();
}
