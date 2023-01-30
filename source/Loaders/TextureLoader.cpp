//
//  TextureLoader.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../dependencies/stb_image/stb_image.hpp"

struct Image{
    uchar* data;
    int width;
    int height;
    int colorChannels;
} image;

void generateTextureId(GLuint* textureId, int texType);
void setTextureParameters(int texType);
void checkTextureFileIsFound(Image* image, cchar* textureFilePath);


GLuint TextureLoader::load2d(cchar* textureFileName) {
    GLuint entityTextureId;
    
    char* textureFilePath = (char*)calloc(sizeof(char),256);
    FileLoader::generatePathForFile(textureFilePath, "textures",textureFileName);
    
    Image* image = (Image*) calloc(sizeof(Image),1);
    stbi_set_flip_vertically_on_load(true);
    image->data = stbi_load(textureFilePath, &image->width, &image->height, &image->colorChannels, 0);
    checkTextureFileIsFound(image, textureFilePath);
    
    generateTextureId(&entityTextureId, GL_TEXTURE_2D);
    setTextureParameters(GL_TEXTURE_2D);
    
    AP_TEST(glTexImage2D(GL_TEXTURE_2D, MI_MIPMAP_0, GL_RGBA, image->width, image->height, MI_BORDER_WIDTH, GL_RGBA, GL_UNSIGNED_BYTE, image->data));
    AP_TEST(glGenerateMipmap(GL_TEXTURE_2D));
    
    stbi_image_free(image->data);
    free(image);
    free(textureFilePath);
    return entityTextureId;
}

GLuint TextureLoader::loadCubemap(std::vector<cchar*> textureFaces) {
    GLuint entityTextureId =0;
    generateTextureId(&entityTextureId, GL_TEXTURE_CUBE_MAP);
    char* textureFilePath = (char*)calloc(sizeof(char),256);
    Image* image = (Image*) malloc(sizeof(Image));
    stbi_set_flip_vertically_on_load(false);
    for (byte x=0; x<textureFaces.size(); x++) {
        FileLoader::generatePathForFile(textureFilePath, "textures", textureFaces[x]);
        image->data = stbi_load(textureFilePath, &image->width, &image->height, &image->colorChannels, 0);
        AP_TEST(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+x, MI_MIPMAP_0, GL_RGB, image->width, image->height, MI_BORDER_WIDTH, GL_RGB, GL_UNSIGNED_BYTE, image->data));
        checkTextureFileIsFound(image, textureFilePath);
        stbi_image_free(image->data);
    }
    free(image);
    free(textureFilePath);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    setTextureParameters(GL_TEXTURE_CUBE_MAP);
    return entityTextureId;
}

void generateTextureId(GLuint* textureId, int texType) {
    AP_TEST(glGenTextures(1, textureId));
    AP_TEST(glBindTexture(texType, *textureId));
}

void setTextureParameters(int texType) {
    AP_TEST(glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    AP_TEST(glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    AP_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    AP_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    AP_TEST(glTexParameteri(texType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

void checkTextureFileIsFound(Image* image, cchar* textureFilePath) {
    if (image->data == NULL) {
        printf("[MI_TXL_ERROR] The requested texture file was not found. Path:\n %s\n",textureFilePath);
        exit(1);
    }
}
