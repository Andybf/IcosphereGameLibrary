//
//  VBO.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/Core/VBO.hpp>

void VBO::bind(GLuint id) {
    AP_TEST(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VBO::unbind() {
    AP_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::deleteObject(GLuint id) {
    AP_TEST(glDeleteBuffers(1, &id));
}

GLuint VBO::generateNewVBO(std::vector<float> vertices,
                           std::vector<float> normals,
                           std::vector<float> texCoords)
{
    ulong modelsSize = vertices.size()*sizeof(GLfloat);
    ulong normalsSize = normals.size()*sizeof(GLfloat);
    ulong texCrdSize = texCoords.size()*sizeof(GLfloat);
    GLuint vertexBufferObjectId = 0;
    
    AP_TEST(glGenBuffers(1, &vertexBufferObjectId));
    AP_TEST(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId));
    AP_TEST(glBufferData(GL_ARRAY_BUFFER,
                         modelsSize+normalsSize+texCrdSize,
                         NULL,
                         GL_DYNAMIC_DRAW));
    
    AP_TEST(glBufferSubData(GL_ARRAY_BUFFER, 0, modelsSize, vertices.data()));
    AP_TEST(glBufferSubData(GL_ARRAY_BUFFER, modelsSize, normalsSize, normals.data()));
    AP_TEST(glBufferSubData(GL_ARRAY_BUFFER,
                            modelsSize+normalsSize,
                            texCrdSize, texCoords.data()));
    return vertexBufferObjectId;
}
