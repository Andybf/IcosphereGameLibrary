//
//  DebugCamera.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/World/Cameras/DebugCamera.hpp>

DebugCamera::DebugCamera(Camera* camera) {
    this->camera = camera;
    this->lastMouseState.x = 0;
    this->lastMouseState.y = 0;
    this->lastMouseState.isRightPressed = false;
    this->lastMouseState.isLeftPressed = false;
    this->actualMouseState.x = 0;
    this->actualMouseState.y = 0;
    this->actualMouseState.isRightPressed = false;
    this->actualMouseState.isLeftPressed = false;
    this->yaw =0;
    this->pitch =0;
}

void DebugCamera::handleMousePress(short buttonPressed, short actionPerformed) {
    if (buttonPressed == AP_MOUSE_BUTTON_RIGHT && actionPerformed == AP_MOUSE_BUTTON_RIGHT) {
        this->actualMouseState.isRightPressed = true;
        if (this->lastMouseState.x == -1.0f) {
            this->lastMouseState.x = this->actualMouseState.x;
            this->lastMouseState.y = this->actualMouseState.y;
        }
    } else if (buttonPressed == AP_MOUSE_BUTTON_RIGHT && actionPerformed == AP_MOUSE_RELEASE) {
        this->actualMouseState.isRightPressed = false;
        this->lastMouseState.x = -1.0f;
        this->lastMouseState.y = -1.0f;
    }
}

void DebugCamera::handleMouseMovement(float x, float y) {
    if (this->actualMouseState.isRightPressed) {
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
        this->camera->setPosition(this->camera->getPosition() + this->camera->getOrientation());
    } else {
        this->camera->setPosition(this->camera->getPosition() - this->camera->getOrientation());
    }
}
