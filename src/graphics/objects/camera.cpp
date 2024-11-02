#include "camera.h"

#include <glm/gtx/transform.hpp>





// Constructeur.
Camera::Camera(glm::vec3 position, Quaternion orientation, unsigned int w, unsigned int h) :
projection(), position(), up(), fwd(), right() {
    projection = glm::perspective(100.0, (double) w / h, 0.1, 1000.0);
    this->position = position;
    setOrientation(orientation);
}



// Destructeur.
Camera::~Camera() {}





// Translate la caméra.
void Camera::translate(glm::vec3 v) {
    position += v;
}



// Oriente la caméra pour qu'elle vise un point donné.
void Camera::lookAt(glm::vec3 v) {

    glm::vec3 lookat = v-position;
    if (glm::length(lookat) != 0) {

        // Calcule les produits scalaires et vectoriels entre l'ancienne
        // et la nouvelle direction de la caméra.
        lookat = glm::normalize(lookat);
        glm::vec3 axis = glm::cross(fwd, lookat);
        double prd = glm::dot(fwd, lookat);

        // En déduit le quaternion de la rotation.
        Quaternion rot;
        rot.x = axis.x;
        rot.y = axis.y;
        rot.z = axis.z;
        rot.w = prd;

        // Effectue la rotation.
        rotation(rot);

    }

}



// Effectue une rotation à partir d'un quaternion.
void Camera::rotation(Quaternion rot) {
    rot.rotation(up);
    rot.rotation(fwd);
    rot.rotation(right);
}





// Permet de définir l'orientation.
void Camera::setOrientation(Quaternion rot) {   

    // Orientation par défaut.
    up = glm::vec3(0.0, 1.0, 0.0);
    fwd = glm::vec3(1.0, 0.0, 0.0);
    right = glm::vec3(0.0, 0.0, 1.0);

    // Effectue la rotation des vecteurs.
    rot.rotation(up);
    rot.rotation(fwd);
    rot.rotation(right);

}



// Permet de définir la position.
void Camera::setPosition(glm::vec3 v) {
    this->position = v;
}





// Renvoie la matrice Projection.
glm::mat4 Camera::getProjection() const {
    return projection;
}



// Renvoie la matrice ModelView.
glm::mat4 Camera::getModelView() const {
    return glm::lookAt(position, position+fwd, up);
}



// Renvoie la position.
glm::vec3 Camera::getPosition() const {
    return position;
}



// Renvoie le vecteur pointant vers le haut.
glm::vec3 Camera::getForward() const {
    return fwd;
}



// Renvoie le vecteur pointqnt vers la droite.
glm::vec3 Camera::getRight() const {
    return right;
}



// Renvoie le verteur pointant vers le haut.
glm::vec3 Camera::getUp() const {
    return up;
}
