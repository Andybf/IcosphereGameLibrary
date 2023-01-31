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
void checkSourceLanguage(char* source);
void convertSourceToES(char* source);
void convertSourceToGL(char* source);


GLuint ShaderLoader::load(cchar* vertexFileName, cchar* fragmentFileName) {
    char* vertexShaderSourcePath   = (char*)calloc(sizeof(char),256);
    char* fragmentShaderSourcePath = (char*)calloc(sizeof(char),256);
    
    FileLoader::generatePathForFile(vertexShaderSourcePath ,"shaders", vertexFileName);
    FileLoader::generatePathForFile(fragmentShaderSourcePath, "shaders", fragmentFileName);
    
    char* vertexShaderSource = FileLoader::read(vertexShaderSourcePath);
    char* fragmentShaderSource = FileLoader::read(fragmentShaderSourcePath);
    
    free(vertexShaderSourcePath);
    free(fragmentShaderSourcePath);
    
    checkSourceLanguage(vertexShaderSource);
    checkSourceLanguage(fragmentShaderSource);
    
    int vertexId = compile(GL_VERTEX_SHADER, vertexShaderSource);
    int fragmentId = compile(GL_FRAGMENT_SHADER, fragmentShaderSource);
    
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

void checkSourceLanguage(char* source) {
    if ( strstr((char*)glGetString(GL_VERSION), "OpenGL ES") ) {
        convertSourceToES(source);
    } else {
        convertSourceToGL(source);
    }
}

void convertSourceToES(char* source) {
    if ( strstr(source, "#version 330") ) {
        source = (char*) realloc(source, strlen(source)+0x4);
        ushort replaceIndex = strstr(source, "330\n") - source;
        char* buffer = (char*) calloc(sizeof(char), strlen(source));
        strcpy(buffer, source+replaceIndex+3);
        strcpy(source+replaceIndex, "300 es");
        strcat(source, buffer);
        free(buffer);
        
        printf("[AP_SHD_INFO] shader automaticly converted to GLSL ES 3.0\n");
    }
}

void convertSourceToGL(char* source) {
    if ( strstr(source, "#version 300 es") ) {
        ushort replaceIndex = strstr(source, "300 es") - source;
        char* buffer = (char*) calloc(sizeof(char), strlen(source));
        strcpy(buffer, source+replaceIndex+6);
        strcpy(source+replaceIndex, "330");
        strcat(source, buffer);
        free(buffer);
        
        printf("[AP_SHD_INFO] shader automaticly converted to GLSL 3.3+\n");
    }
}
