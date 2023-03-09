//
//  DebugCamera.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "./DebugCamera.hpp"

DebugCamera::DebugCamera(Camera* camera) {
    this->camera = camera;
    this->lastMouseState.x = 0;
    this->lastMouseState.y = 0;
    this->lastMouseState.isActivationButtonPressed = false;
    this->lastMouseState.isLeftPressed = false;
    this->actualMouseState.x = 0;
    this->actualMouseState.y = 0;
    this->actualMouseState.isActivationButtonPressed = false;
    this->actualMouseState.isLeftPressed = false;
    this->yaw =0;
    this->pitch =0;
}

void DebugCamera::handleMouseClickDown() {
    this->actualMouseState.isActivationButtonPressed = true;
    if (this->lastMouseState.x == -1.0f) {
        this->lastMouseState.x = this->actualMouseState.x;
        this->lastMouseState.y = this->actualMouseState.y;
    }
}

void DebugCamera::handleMouseClickUp() {
    this->actualMouseState.isActivationButtonPressed = false;
    this->lastMouseState.x = -1.0f;
    this->lastMouseState.y = -1.0f;
}

void DebugCamera::handleMouseMovement(float x, float y) {
    if (this->actualMouseState.isActivationButtonPressed) {
        this->yaw -= (actualMouseState.x - x);
        this->pitch += (actualMouseState.y - y);
        if (this->pitch > 90.0f) {
            this->pitch = 89.99f;
        }
        if (this->pitch < -90.0f) {
            this->pitch = -89.99f;
        }
        this->camera->setOrientation(yaw, pitch);
    }
    if (y != this->actualMouseState.y) {
        this->lastMouseState.x = this->actualMouseState.x;
        this->lastMouseState.y = this->actualMouseState.y;
    }
    this->actualMouseState.x = x;
    this->actualMouseState.y = y;
}

void DebugCamera::handleMouseScroll(float x, float y) {
    if (y > 0) {
        this->camera->setPosition(glm::vec3(this->camera->getPosition().x,
                                            this->camera->getPosition().y,
                                            this->camera->getPosition().z +0.25f));
    } else {
        this->camera->setPosition(glm::vec3(this->camera->getPosition().x,
                                            this->camera->getPosition().y,
                                            this->camera->getPosition().z -0.25f));
        //this->camera->setPosition(this->camera->getPosition() - this->camera->getOrientation());
    }
}
