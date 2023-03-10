//
//  TextureLoader.cpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "./TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../dependencies/stb_image/stb_image.hpp"

void generateTextureId(GLuint* textureId, int texType);
void setTextureParameters(int texType);
void checkTextureFileIsFound(Image* image, cchar* textureFilePath);

struct Image* TextureLoader::loadFromFile(cchar* textureFileName) {
    char* textureFilePath = (char*)calloc(sizeof(char),256);
    FileLoader::generatePathForFile(textureFilePath, "textures",textureFileName);
    Image* image = (Image*) calloc(sizeof(Image),1);
    
    stbi_set_flip_vertically_on_load(true);
    image->data = stbi_load(textureFilePath, &image->width, &image->height, &image->colorChannels, 0);
    checkTextureFileIsFound(image, textureFilePath);
    
    free(textureFilePath);
    return image;
}


GLuint TextureLoader::load2d(struct Image* imageData) {
    GLuint entityTextureId = 0;
    generateTextureId(&entityTextureId, GL_TEXTURE_2D);
    setTextureParameters(GL_TEXTURE_2D);
    IC_TEST(glTexImage2D(GL_TEXTURE_2D,
                         MI_MIPMAP_0,
                         GL_RGBA,
                         imageData->width,
                         imageData->height,
                         MI_BORDER_WIDTH,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         imageData->data));
    IC_TEST(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(imageData->data);
    free(imageData);
    return entityTextureId;
}

GLuint TextureLoader::loadCubemap(std::vector<struct Image*> imageDataVector) {
    GLuint entityTextureId = 0;
    generateTextureId(&entityTextureId, GL_TEXTURE_CUBE_MAP);
    for (byte x=0; x<imageDataVector.size(); x++) {
        IC_TEST(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+x,
                             MI_MIPMAP_0,
                             GL_RGB,
                             imageDataVector.at(x)->width,
                             imageDataVector.at(x)->height,
                             MI_BORDER_WIDTH,
                             GL_RGB,
                             GL_UNSIGNED_BYTE,
                             imageDataVector.at(x)->data));
        stbi_image_free(imageDataVector.at(x)->data);
    }
    imageDataVector.clear();
    imageDataVector.shrink_to_fit();
#ifndef __EMSCRIPTEN__
    IC_TEST(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
#endif
    setTextureParameters(GL_TEXTURE_CUBE_MAP);
    return entityTextureId;
}

void generateTextureId(GLuint* textureId, int texType) {
    IC_TEST(glGenTextures(1, textureId));
    IC_TEST(glBindTexture(texType, *textureId));
}

void setTextureParameters(int texType) {
    IC_TEST(glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    IC_TEST(glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    IC_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    IC_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    IC_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

void checkTextureFileIsFound(Image* image, cchar* textureFilePath) {
    if (image->data == NULL) {
        printf("[IC_TXL_ERROR] The requested texture file was not found. Path:\n %s\n",textureFilePath);
        exit(1);
    }
}
