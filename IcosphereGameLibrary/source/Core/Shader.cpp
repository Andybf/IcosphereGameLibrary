//
//  Shader.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Icosphere/Core/Shader.hpp>

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
    IC_TEST(glBindVertexArray(entity->mesh->vaoId));
    setUniformMatrix("modelMatrix", entity->getMatrix());
    setUniformMatrix("viewMatrix", camera);
    setUniformMatrix("projectionMatrix", projection);
}

void Shader::setUniformModelProjection(Entity* entity, glm::mat4 projection) {
    IC_TEST(glBindVertexArray(entity->mesh->vaoId));
    setUniformMatrix("modelMatrix", entity->getMatrix());
    setUniformMatrix("projectionMatrix", projection);
}

void Shader::setUniformTexture(uint textureId, uint dimensions) {
    IC_TEST(glUniform1i(glGetUniformLocation(activeShaderId, "texture0"),
                        textureId-1));
    IC_TEST(glActiveTexture(GL_TEXTURE0 + textureId- 1));
    IC_TEST(glBindTexture(dimensions, textureId));
}

void Shader::setUniformIntArray(cchar* name, int* intArray, int size) {
    IC_TEST(glUniform1iv(glGetUniformLocation(activeShaderId,name),
                         size*sizeof(int),
                         intArray));
}

void Shader::setUniformFloat(cchar* name, float value) {
    IC_TEST(glUniform1f(glGetUniformLocation(activeShaderId,name), value));
}

void Shader::setUniformVec2Array(cchar* name, const float* value, int size) {
    IC_TEST(glUniform2fv(glGetUniformLocation(activeShaderId,name),size,value));
}

void Shader::setUniformVec3(cchar* name, glm::vec3 value) {
    IC_TEST(glUniform3f(glGetUniformLocation(activeShaderId,name),
                        value.x,
                        value.y,
                        value.z));
}

void setUniformMatrix(cchar* name, glm::mat4 matrix) {
    IC_TEST(glUniformMatrix4fv(glGetUniformLocation(activeShaderId,name),
                               IC_COUNT,
                               GL_FALSE,
                               &matrix[0][0]));
}
