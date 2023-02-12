//
//  VAO.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Icosphere/Core/VAO.hpp>

void VAO::bind(GLuint id) {
    IC_TEST(glBindVertexArray(id));
}

void VAO::unbind() {
    IC_TEST(glBindVertexArray(0));
}

void VAO::deleteObject(GLuint id) {
    IC_TEST(glDeleteVertexArrays(1, &id));
}

GLuint VAO::generateNewVAO() {
    GLuint vertexArrayObject = 0;
    IC_TEST(glGenVertexArrays(IC_VAO_TO_GENERATE, &vertexArrayObject));
    return vertexArrayObject;
}

void VAO::linkAttribute(GLuint vertexArrayObject,
                        GLuint shaderAttribute,
                        short numElements,
                        ulong offset)
{
    IC_TEST(glEnableVertexAttribArray(shaderAttribute));
    IC_TEST(glVertexAttribPointer(shaderAttribute,
                                  numElements,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  IC_STRIDE,
                                  BUFFER_OFFSET(offset)));
}
