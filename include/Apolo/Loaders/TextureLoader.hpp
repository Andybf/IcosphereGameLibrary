//
//  TextureLoader.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include "../Core.hpp"
#include "FileLoader.hpp"

#define MI_MIPMAP_0 0
#define MI_BORDER_WIDTH 0

namespace TextureLoader {

    GLuint load2d(cchar* textureFilePath);
    GLuint loadCubemap(std::vector<cchar*> textureFaces);
    
};

#endif /* TextureLoader_hpp */
