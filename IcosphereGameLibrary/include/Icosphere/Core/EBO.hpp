//
//  EBO.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef EBO_hpp
#define EBO_hpp

#include "../Core.hpp"

namespace EBO {
    void bind(GLuint id);
    void unbind();
    void deleteObject(GLuint id);
    GLuint generateNewEBO(std::vector<uint>* indices);
}


#endif /* EBO_hpp */
