//
//  VAO.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/Core/VAO.hpp>

void VAO::bind(GLuint id) {
    AP_TEST(glBindVertexArray(id));
}

void VAO::unbind() {
    AP_TEST(glBindVertexArray(0));
}

void VAO::deleteObject(GLuint id) {
    AP_TEST(glDeleteVertexArrays(1, &id));
}

GLuint VAO::generateNewVAO() {
    GLuint vertexArrayObject = 0;
    AP_TEST(glGenVertexArrays(AP_VAO_TO_GENERATE, &vertexArrayObject));
    return vertexArrayObject;
}

void VAO::linkAttribute(GLuint vertexArrayObject,
                        GLuint shaderAttribute,
                        short numElements,
                        ulong offset)
{
    AP_TEST(glEnableVertexAttribArray(shaderAttribute));
    AP_TEST(glVertexAttribPointer(shaderAttribute,
                                  numElements,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  AP_STRIDE,
                                  BUFFER_OFFSET(offset)));
}
