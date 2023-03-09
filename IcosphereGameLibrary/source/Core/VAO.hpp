//
//  VAO.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef VAO_hpp
#define VAO_hpp

#include "../Core.hpp"

namespace VAO {
    void bind(GLuint id);
    void unbind();
    void deleteObject(GLuint id);

    GLuint generateNewVAO();
    void linkAttribute(GLuint vertexArrayObject,
                              GLuint shaderAttribute,
                              short numElements,
                              ulong offset);
}



#endif /* VAO_hpp */
