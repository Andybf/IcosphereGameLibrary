//
//  TextureLoader.hpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include "../Core.hpp"
#include "FileLoader.hpp"

#define MI_MIPMAP_0 0
#define MI_BORDER_WIDTH 0

struct Image{
    uchar* data;
    int width;
    int height;
    int colorChannels;
};

namespace TextureLoader {

    struct Image* loadFromFile(cchar* textureFileName);
    GLuint load2d(struct Image* imageData);
    GLuint loadCubemap(std::vector<struct Image*> imageDataVector);
    
};

#endif /* TextureLoader_hpp */
