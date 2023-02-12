//
//  VBO.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Icosphere/Core/VBO.hpp>

void VBO::bind(GLuint id) {
    IC_TEST(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VBO::unbind() {
    IC_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::deleteObject(GLuint id) {
    IC_TEST(glDeleteBuffers(1, &id));
}

GLuint VBO::generateNewVBO(std::vector<float> vertices,
                           std::vector<float> normals,
                           std::vector<float> texCoords)
{
    ulong modelsSize = vertices.size()*sizeof(GLfloat);
    ulong normalsSize = normals.size()*sizeof(GLfloat);
    ulong texCrdSize = texCoords.size()*sizeof(GLfloat);
    GLuint vertexBufferObjectId = 0;
    
    IC_TEST(glGenBuffers(1, &vertexBufferObjectId));
    IC_TEST(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId));
    IC_TEST(glBufferData(GL_ARRAY_BUFFER,
                         modelsSize+normalsSize+texCrdSize,
                         NULL,
                         GL_DYNAMIC_DRAW));
    
    IC_TEST(glBufferSubData(GL_ARRAY_BUFFER, 0, modelsSize, vertices.data()));
    IC_TEST(glBufferSubData(GL_ARRAY_BUFFER, modelsSize, normalsSize, normals.data()));
    IC_TEST(glBufferSubData(GL_ARRAY_BUFFER,
                            modelsSize+normalsSize,
                            texCrdSize, texCoords.data()));
    return vertexBufferObjectId;
}
