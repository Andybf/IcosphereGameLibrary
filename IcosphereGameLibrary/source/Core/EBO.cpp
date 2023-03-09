//
//  EBO.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "./EBO.hpp"

void EBO::bind(GLuint id) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::deleteObject(GLuint id) {
    glDeleteBuffers(1, &id);
}
GLuint EBO::generateNewEBO(std::vector<uint>* indices) {
    GLuint elementBufferObjectId = 0;
    IC_TEST(glGenBuffers(1, &elementBufferObjectId));
    IC_TEST(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId));
    IC_TEST(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         indices->size()*sizeof(uint),
                         indices->data(),
                         GL_STATIC_DRAW));
    return elementBufferObjectId;
}
