//
//  Shader.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/Core/Shader.hpp>

static uint activeShaderId = 0;
static void setUniformMatrix(cchar* name, glm::mat4 matrix);



void Shader::setActiveProgram(uint shaderId) {
    glUseProgram(shaderId);
    activeShaderId = shaderId;
}

uint Shader::getActiveShaderId(){
    return activeShaderId;
}

void Shader::setUniformModelViewProjection(Entity* entity,
                                           glm::mat4 camera,
                                           glm::mat4 projection)
{
    AP_TEST(glBindVertexArray(entity->mesh->vaoId));
    setUniformMatrix("modelMatrix", entity->getMatrix());
    setUniformMatrix("viewMatrix", camera);
    setUniformMatrix("projectionMatrix", projection);
}

void Shader::setUniformModelProjection(Entity* entity, glm::mat4 projection) {
    AP_TEST(glBindVertexArray(entity->mesh->vaoId));
    setUniformMatrix("modelMatrix", entity->getMatrix());
    setUniformMatrix("projectionMatrix", projection);
}

void Shader::setUniformTexture(uint textureId, uint dimensions) {
    AP_TEST(glUniform1i(glGetUniformLocation(activeShaderId, "texture0"),
                        textureId-1));
    AP_TEST(glActiveTexture(GL_TEXTURE0 + textureId- 1));
    AP_TEST(glBindTexture(dimensions, textureId));
}

void Shader::setUniformIntArray(cchar* name, int* intArray, int size) {
    AP_TEST(glUniform1iv(glGetUniformLocation(activeShaderId,name),
                         size*sizeof(int),
                         intArray));
}

void Shader::setUniformFloat(cchar* name, float value) {
    AP_TEST(glUniform1f(glGetUniformLocation(activeShaderId,name), value));
}

void Shader::setUniformVec2Array(cchar* name, const float* value, int size) {
    AP_TEST(glUniform2fv(glGetUniformLocation(activeShaderId,name),size,value));
}

void Shader::setUniformVec3(cchar* name, glm::vec3 value) {
    AP_TEST(glUniform3f(glGetUniformLocation(activeShaderId,name),
                        value.x,
                        value.y,
                        value.z));
}

void setUniformMatrix(cchar* name, glm::mat4 matrix) {
    AP_TEST(glUniformMatrix4fv(glGetUniformLocation(activeShaderId,name),
                               AP_COUNT,
                               GL_FALSE,
                               &matrix[0][0]));
}
