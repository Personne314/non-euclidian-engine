#include "camera.h"

#include <glm/gtx/transform.hpp>
#include <cmath>



// Constructor.
// position : camera position in 3D space.
// orientation : quaternion used to define the orientation of the camera 
// from the canonical basis.
// w,h : screen dimension.
Camera::Camera(glm::vec3 position, Quaternion orientation, unsigned int w, unsigned int h) :
projection(), position(), up(), fwd(), right() {
	projection = glm::perspective(100.0, (double) w / h, 0.1, 1000.0);
	this->position = position;
	fwd = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	right = glm::vec3(0.0, 0.0, 1.0);
	rotation(orientation);
}

// Constructor.
// position : camera position in 3D space.
// direction : where the camera is supposed to look at.
// w,h : screen dimension.
Camera::Camera(glm::vec3 position, glm::vec3 direction, unsigned int w, unsigned int h) {
	projection = glm::perspective(70.0, (double) w / h, 0.1, 1000.0);
	this->position = position;
	fwd = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	right = glm::vec3(0.0, 0.0, 1.0);
	lookAt(direction);
}

// Destructor.
Camera::~Camera() {}


// Translates the camera.
void Camera::translate(glm::vec3 v) {
	position += v;
}

// Rotate the camera to point at v.
void Camera::lookAt(glm::vec3 v) {
	glm::vec3 lookat = v-position;
	if (glm::length(lookat) != 0) {

		// Calculates the dot and vectorial products.
		lookat = glm::normalize(lookat);
		glm::vec3 axis = glm::cross(fwd, lookat);
		double prd = glm::dot(fwd, lookat);

		// Case of colinearity.
		if (axis.length() == 0) {
			if (prd > 0) return;
			fwd = -fwd;
			up = -up;
			right = -right;
			return;
		}

		// Rotate the camera.
		rotation(Quaternion(axis, std::acos(prd)));

	}

}

// Rotate the camera using a quaternion.
void Camera::rotation(Quaternion rot) {
	rot.rotation(up);
	rot.rotation(fwd);
	rot.rotation(right);
}

// Sets camera position.
void Camera::setPosition(glm::vec3 v) {
	this->position = v;
}


// Returns the projection matrix.
// Used to project 3D point into 2D plane.
glm::mat4 Camera::getProjection() const {
	return projection;
}

// Returns the modelview matrix.
// Used when doing position/orientation transformations.
glm::mat4 Camera::getModelView() const {
	return glm::lookAt(position, position+fwd, up);
}

// Returns camera position.
glm::vec3 Camera::getPosition() const {
	return position;
}

// Getters for camera basis.
// Returns forward vector.
glm::vec3 Camera::getForward() const {
	return fwd;
}

// Returns right vector.
glm::vec3 Camera::getRight() const {
	return right;
}

// Returns up vector.
glm::vec3 Camera::getUp() const {
	return up;
}
