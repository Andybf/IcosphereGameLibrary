//
//  ShaderLoader.hpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp

#include "../Core.hpp"
#include "./FileLoader.hpp"

namespace ShaderLoader {
    
    GLuint load(cchar* vertexFileName, cchar* fragmentFileName);

};

#endif /* ShaderLoader_hpp */
