//
//  ShaderLoader.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/Loaders/ShaderLoader.hpp>

GLuint compile(int shaderType, char* sourceContents);
GLuint link(int vextexId, int fragmentId);
void check(int status, int shaderId);


GLuint ShaderLoader::load(cchar* vertexFileName, cchar* fragmentFileName) {
    char* vertexShaderSourcePath   = (char*)calloc(sizeof(char),256);
    char* fragmentShaderSourcePath = (char*)calloc(sizeof(char),256);
    
    FileLoader::generatePathForFile(vertexShaderSourcePath ,"shaders", vertexFileName);
    FileLoader::generatePathForFile(fragmentShaderSourcePath, "shaders", fragmentFileName);
    
    char* vertexShaderSource = FileLoader::read(vertexShaderSourcePath);
    char* fragmentShaderSource = FileLoader::read(fragmentShaderSourcePath);
    
    int vertexId = compile(GL_VERTEX_SHADER, vertexShaderSource);
    int fragmentId = compile(GL_FRAGMENT_SHADER, fragmentShaderSource);
    
    free(vertexShaderSourcePath);
    free(fragmentShaderSourcePath);
    free(vertexShaderSource);
    free(fragmentShaderSource);
    
    return link(vertexId, fragmentId);
}

GLuint compile(int shaderType, char* sourceContents) {
    GLuint shaderId = glCreateShader(shaderType);
    AP_TEST(glShaderSource(shaderId, 1, (cchar**)&sourceContents, 0));
    AP_TEST(glCompileShader(shaderId));
    check(GL_COMPILE_STATUS, shaderId);
    return shaderId;
}

GLuint link(int vertexId, int fragmentId) {
    GLuint shaderProgramId = glCreateProgram();
    AP_TEST(glAttachShader(shaderProgramId, vertexId));
    AP_TEST(glAttachShader(shaderProgramId, fragmentId));
    AP_TEST(glLinkProgram(shaderProgramId));
#ifndef __EMSCRIPTEN__
    check(GL_LINK_STATUS, shaderProgramId);
#endif
    return shaderProgramId;
}

void check(int status, int shaderId) {
    int isShaderSuccessfullyCompiled = -1;
    AP_TEST(glGetShaderiv(shaderId, status, &isShaderSuccessfullyCompiled));
    if (!isShaderSuccessfullyCompiled) {
        char* infoLog = (char*) malloc(sizeof(char)*512);
        AP_TEST(glGetShaderInfoLog(shaderId, 512, NULL, infoLog));
        printf("[AP_SHD_ERROR] shaderId %d unchecked:\n%s\n",shaderId,infoLog);
        free(infoLog);
        exit(1);
    }
}
