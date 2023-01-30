//
//  Entity.c
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "../include/Apolo/World/Entity.hpp"

Entity::Entity() {
    this->matrix = glm::mat4(1.0f);
    this->isEnabled = true;
    this->textureType = GL_TEXTURE_2D;
    this->modelDrawType = GL_TRIANGLES;
    this->relatedShaderId = 0;
    this->relatedTextureId = 0;
}

glm::mat4 Entity::getMatrix() {
    return this->matrix;
}

void Entity::setScale(glm::vec3 scale) {
    this->matrix = glm::scale(this->matrix, scale);
}
glm::vec3 Entity::getScale() {
    glm::vec3 scale;
    for (short i = 0; i < 3; ++i) {
        scale[i] = glm::length(this->matrix[i]);
        this->matrix[i] /= scale[i];
    }
    return scale;
}

void Entity::setPosition(glm::vec3 position) {
    this->matrix = glm::translate(position);
}
void Entity::addToPosition(glm::vec3 position) {
    this->matrix = glm::translate(this->matrix,position);
}
glm::vec3 Entity::getPosition() {
    return this->matrix[3];
}

void Entity::setOrientation(float angle, glm::vec3 orientation) {
    this->matrix = glm::rotate(this->matrix, glm::radians(angle), orientation);
}
glm::quat Entity::getOrientation() {
    return glm::quat_cast(this->matrix);
}
