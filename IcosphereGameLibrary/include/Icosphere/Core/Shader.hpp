//
//  Shader.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "../Core.hpp"
#include "../World/Entity.hpp"

namespace Shader {
    void setActiveProgram(uint shaderId);
    uint getActiveShaderId();

    void setUniformModelViewProjection(Entity* entity, glm::mat4 camera, glm::mat4 projection);
    void setUniformModelProjection(Entity* entity, glm::mat4 projection);

    void setUniformTexture(uint textureId, uint dimensions);
    void setUniformIntArray(cchar* name, int* intArray, int size);
    void setUniformFloat(cchar* name, float value);
    void setUniformVec2Array(cchar* name, const float* value, int size);
    void setUniformVec3(cchar* name, glm::vec3 value);
}

#endif /* Shader_hpp */
