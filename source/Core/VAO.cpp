//
//  VAO.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "../include/Apolo/Core/VAO.hpp"

void VAO::bind(GLuint id) {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::deleteObject(GLuint id) {
    glDeleteVertexArrays(1, &id);
}

GLuint VAO::generateNewVAO() {
    GLuint vertexArrayObject = 0;
    glGenVertexArrays(AP_VAO_TO_GENERATE, &vertexArrayObject);
    return vertexArrayObject;
}

void VAO::linkAttribute(GLuint vertexArrayObject, GLuint shaderAttribute, short numElements, ulong offset) {
    glEnableVertexAttribArray(shaderAttribute);
    glVertexAttribPointer(shaderAttribute, numElements, GL_FLOAT, GL_FALSE, AP_STRIDE, BUFFER_OFFSET(offset));
}
