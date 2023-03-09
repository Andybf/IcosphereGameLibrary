//
//  ShaderLoader.cpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "./ShaderLoader.hpp"

GLuint compile(int shaderType, char* sourceContents);
GLuint link(int vextexId, int fragmentId);
GLint checkShaderStatus(GLenum status, GLuint shaderId);
GLint checkProgramStatus(GLenum status, GLuint programId);
void checkParam(GLuint returnedParameter, GLint programShader, GLint status);
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
    
#ifdef IC_DEBUG
        printf("[IC_SHD_INFO] Loading shaders:\n %s\n %s\n",vertexFileName,fragmentFileName);
#endif
    
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
    IC_TEST(glShaderSource(shaderId, 1, (cchar**)&sourceContents, 0));
    IC_TEST(glCompileShader(shaderId));
    checkShaderStatus(GL_COMPILE_STATUS, shaderId);
    return shaderId;
}

GLuint link(int vertexId, int fragmentId) {
    GLuint shaderProgramId = glCreateProgram();
    IC_TEST(glAttachShader(shaderProgramId, vertexId));
    IC_TEST(glAttachShader(shaderProgramId, fragmentId));
    IC_TEST(glLinkProgram(shaderProgramId));
    checkProgramStatus(GL_LINK_STATUS, shaderProgramId);
    return shaderProgramId;
}

GLint checkShaderStatus(GLenum status, GLuint shaderId) {
    GLint returnedParameter = -1;
    IC_TEST(glGetShaderiv(shaderId, status, &returnedParameter));
    checkParam(returnedParameter, shaderId, status);
    return returnedParameter;
}
GLint checkProgramStatus(GLenum status, GLuint programId) {
    GLint returnedParameter = -1;
    IC_TEST(glGetProgramiv(programId, status, &returnedParameter));
    checkParam(returnedParameter, programId, status);
    return returnedParameter;
}

void checkParam(GLuint returnedParameter, GLint programShader, GLint status) {
    if (!returnedParameter) {
        char* infoLog = (char*) malloc(sizeof(char)*512);
        IC_TEST(glGetShaderInfoLog(programShader, 512, NULL, infoLog));
        printf("[IC_SHD_ERROR] GL status check: 0x%x\nProgram/ShaderId %d is invalid:\n%s\n",
               status,
               programShader,
               infoLog);
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
#ifdef IC_DEBUG
        printf("[IC_SHD_INFO] shader automaticly converted to GLSL ES 3.0\n");
#endif
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
#ifdef IC_DEBUG
        printf("[IC_SHD_INFO] shader automaticly converted to GLSL 3.3+\n");
#endif
    }
}
