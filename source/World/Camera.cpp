//
//  Camera.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "Camera.hpp"

Camera::Camera() {
    this->matrix = glm::mat4(1.0f);
    this->position = glm::vec3(0.0f,0.0f,-1.0f);
    this->orientation = glm::vec3(0.0f,0.0f,-1.0f);
    this->upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getMatrix() {
    return glm::lookAt(this->position, this->position+this->orientation, this->upAxis);
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}
glm::vec3 Camera::getPosition() {
    return this->position;
}

void Camera::setOrientation(float yaw, float pitch) {
    this->orientation = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                                                 sin(glm::radians(pitch)),
                                                 sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
}
glm::vec3 Camera::getOrientation() {
    return this->orientation;
}
