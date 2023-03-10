//
//  VBO.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef VBO_hpp
#define VBO_hpp

#include "../Core.hpp"

namespace VBO {
    void bind(GLuint id);
    void unbind();
    void deleteObject(GLuint id);
    GLuint generateNewVBO(std::vector<GLfloat> vertices,
                          std::vector<GLfloat> colors,
                          std::vector<GLfloat> normals,
                          std::vector<GLfloat> texCoords);
}

#endif /* VBO_hpp */
