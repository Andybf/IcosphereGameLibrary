//
//  EBO.cpp
//  MinervaEngine
//
//  Created by Anderson on 18/02/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//

#include "EBO.hpp"

EBO::EBO() {
    
}

void EBO::bind(GLuint id) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteObject(GLuint id) {
    glDeleteBuffers(1, &id);
}

GLuint EBO::generateNewEBO(Entity* entity) {
    GLuint elementBufferObjectId = 0;
    glGenBuffers(1, &elementBufferObjectId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, entity->indices.size()*sizeof(GLfloat), entity->indices.data(), GL_STATIC_DRAW);
    return elementBufferObjectId;
}
