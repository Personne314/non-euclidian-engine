#pragma once

#include <glm/glm.hpp>
#include "../../maths/quaternion.h"



// Class Camera : Used to create a quaternion-based camera.
class Camera {

public :

    // Constructors, destructor.
    Camera(glm::vec3 position, Quaternion orientation, unsigned int w, unsigned int h);
    Camera(glm::vec3 position, glm::vec3 direction, unsigned int w, unsigned int h);
    ~Camera();

    // Moving functions.
    void setPosition(glm::vec3 v);
    void translate(glm::vec3 v);
    void lookAt(glm::vec3 v);
    void rotation(Quaternion rot);

    // Getters.
    glm::mat4 getProjection() const;
    glm::mat4 getModelView() const;
    glm::vec3 getPosition() const;
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

private :

    // Projection matrix and camera position.
    glm::mat4 projection;
    glm::vec3 position;

    // camera basis.
    glm::vec3 up;
    glm::vec3 fwd;
    glm::vec3 right;

};
