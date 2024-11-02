#pragma once

#include <glm/glm.hpp>
#include "../../maths/quaternion.h"



// Class Camera : Permet de modéliser une caméra utilisant des quaternions pour les rotations.
class Camera {

public :

    // Constructeur, destructeur.
    Camera(glm::vec3 position, Quaternion orientation, unsigned int w, unsigned int h);
    ~Camera();

    // Fonctions de déplacement.
    void translate(glm::vec3 v);
    void lookAt(glm::vec3 v);
    void rotation(Quaternion rot);

    // Setters.
    void setOrientation(Quaternion rot);
    void setPosition(glm::vec3 v);

    // Getters.
    glm::mat4 getProjection() const;
    glm::mat4 getModelView() const;
    glm::vec3 getPosition() const;
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

private :

    // Position et matrice de projection.
    glm::mat4 projection;
    glm::vec3 position;

    // Repère de la caméra.
    glm::vec3 up;
    glm::vec3 fwd;
    glm::vec3 right;

};
