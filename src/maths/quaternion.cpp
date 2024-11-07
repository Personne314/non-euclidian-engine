#include "quaternion.h"

#include <cmath>



// Constructor.
Quaternion::Quaternion() {
	Quaternion(0,0,0,1);
}

// Copy constructor.
Quaternion::Quaternion(const Quaternion &q) {
	this->w = q.w;
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
}

// Constructor.
Quaternion::Quaternion(glm::vec3 axis, float angle) {
	axis = glm::normalize(axis);
	float s = std::sin(angle/2.0);
	this->w = std::cos(angle/2.0);
	this->x = s*axis.x;
	this->y = s*axis.y;
	this->z = s*axis.z;
}

// Constructor.
Quaternion::Quaternion(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

// Destructor.
Quaternion::~Quaternion() {
}


// Quaternion addition.
Quaternion operator+(Quaternion q1, const Quaternion& q2) {
	q1.x += q2.x; q1.y += q2.y; q1.z += q2.z; q1.w += q2.w;
	return q1;
}

// Quaternion substraction.
Quaternion operator-(Quaternion q1, const Quaternion& q2) {
	q1.x -= q2.x; q1.y -= q2.y; q1.z -= q2.z; q1.w -= q2.w;
	return q1;
}

// Quaternion negation.
Quaternion operator-(Quaternion q) {
	q.x = -q.x; q.y = -q.y; q.z = -q.z; q.w = -q.w;
	return q;
}

// Quaternion multiplication.
Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion (
		q1.w*q2.x + q1.x*q2.x + q1.y*q2.z - q1.z*q2.y,
		q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
		q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w,
		q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z
	);
}

// Right scalar multiplication.
Quaternion operator*(Quaternion q, float v) {
	q.x *= v; q.y *= v; q.z *= v; q.w *= v;
	return q;
}

// Right scalar division.
Quaternion operator/(Quaternion q, float v) {
	q.x /= v; q.y /= v; q.z /= v; q.w /= v;
	return q;
}

// Left scalar multiplication.
Quaternion operator*(float v, Quaternion q) {
	q.x *= v; q.y *= v; q.z *= v; q.w *= v;
	return q;
}

// Left scalar division.
Quaternion operator/(float v, Quaternion q) {
	return Quaternion(0,0,0,v) * q.inv();
}
// Affectation operator.
Quaternion& Quaternion::operator=(const Quaternion& q) {
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
	return *this;
}

// Addition affectation operator.
Quaternion& Quaternion::operator+=(const Quaternion& q) {
	this->x += q.x;
	this->y += q.y;
	this->z += q.z;
	this->w += q.w;
	return *this;
}

// Substraction affectation operator.
Quaternion& Quaternion::operator-=(const Quaternion& q) {
	this->x -= q.x;
	this->y -= q.y;
	this->z -= q.z;
	this->w -= q.w;
	return *this;
}

// Multiplication affectation operator.
Quaternion& Quaternion::operator*=(const Quaternion& q) {
	Quaternion res = (*this)*q;
	(*this) = res;
	return *this;
}

// Scalar multiplication affectation operator.
Quaternion& Quaternion::operator*=(const float v) {
	this->x *= v;
	this->y *= v;
	this->z *= v;
	this->w *= v;
	return *this;
}

// Division affectation operator.
Quaternion& Quaternion::operator/=(const float v) {
	this->x /= v;
	this->y /= v;
	this->z /= v;
	this->w /= v;
	return *this;
}


// Vector rotation by this quaternion.
void Quaternion::rotation(glm::vec3& v) const {
	glm::vec3 xyz = glm::vec3(x,y,z);
	glm::vec3 t = 2.0f*glm::cross(xyz, v);
	v += w*t + glm::cross(xyz, t);
}


// Normalizes the quaternion.
Quaternion& Quaternion::normalize() {
	return (*this) /= norm();
}


// Returns the quaternion norm.
float Quaternion::norm() const {
	return sqrt(x*x + y*y + z*z + w*w);
}

// Returns this quaternion normalized.
Quaternion Quaternion::normalized() const {
	float n = norm();
	return Quaternion(x/n, y/n, z/n, w/n);
}

// Returns this quaternion conjuguate.
Quaternion Quaternion::conj() const {
	return Quaternion(-x, -y, -z, w);
}

// Returns this quaternion inverse.
Quaternion Quaternion::inv() const {
	float n = norm();
	return conj() / (n*n);
}

// Convert this quaternion into it string representation.
std::string Quaternion::to_string() const {
	return "[" + std::to_string(x) + ", " + std::to_string(y) 
		+ ", " + std::to_string(z) + ", " + std::to_string(w) + "]";
}
