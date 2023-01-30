//
//  ShaderLoader.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "ShaderLoader.hpp"

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
    glShaderSource(shaderId, 1, (cchar**)&sourceContents, 0);
    glCompileShader(shaderId);
    check(GL_COMPILE_STATUS, shaderId);
    return shaderId;
}

GLuint link(int vextexId, int fragmentId) {
    GLuint shaderProgramId = glCreateProgram();
    AP_TEST(glAttachShader(shaderProgramId, vextexId));
    AP_TEST(glAttachShader(shaderProgramId, fragmentId));
    AP_TEST(glLinkProgram(shaderProgramId));
    check(GL_LINK_STATUS,shaderProgramId);
    return shaderProgramId;
}

void check(int status, int shaderId) {
    int isShaderSuccessfullyCompiled = -1;
    glGetShaderiv(shaderId, status, &isShaderSuccessfullyCompiled);
    if (!isShaderSuccessfullyCompiled) {
        char* infoLog = (char*) malloc(sizeof(char)*512);
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        printf("[ERROR] shaderId %d unchecked:\n%s\n",shaderId,infoLog);
        free(infoLog);
        exit(1);
    }
}
