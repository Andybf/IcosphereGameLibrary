//
//  core.h
//  Icosphere
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#ifndef core_h
#define core_h

// C includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// C++ includes
#include <vector>

#include "../dependencies/glm/glm.hpp"
#include "../dependencies/glm/gtx/euler_angles.hpp"
#include "../dependencies/glm/gtx/matrix_decompose.hpp"
#include "../dependencies/glm/gtc/random.hpp"
#include "../dependencies/glm/gtx/rotate_vector.hpp"

#ifdef __APPLE__
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #include <OpenGL/gl3.h>
    #include <unistd.h>
#endif

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <GLES3/gl3.h>
#endif

#ifdef IC_DEBUG
    #define IC_TEST(glFunctionCall)\
        while(glGetError() != GL_NO_ERROR);\
        glFunctionCall;\
        while (GLenum errorCode = glGetError()) {\
            printf("[GL_ERROR] code: %d 0x%x | line: %d | file: %s\n",errorCode, errorCode, __LINE__, __FILE__);\
        }
#else
    #define IC_TEST(glFunctionCall)\
        glFunctionCall
#endif

#define IC_IS_FUNCTION_DEFINED(function) *function

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define IC_STRIDE 0
#define IC_VAO_TO_GENERATE 1

#define IC_TEXCOORD_ST 2
#define IC_TEXCOORD_STR 3
#define IC_NORMALS_IJK 3
#define IC_VECTORS_XY 2
#define IC_VECTORS_XYZ 3
#define IC_VECTORS_XYZW 4
#define IC_COLORS_RGB 3
#define IC_COLORS_RGBA 4

#define IC_STARTING_INDEX 0
#define IC_COUNT 1

#define IC_SIZE_CHAR 1
#define IC_SIZE_SHORT 2
#define IC_SIZE_INT 4
#define IC_SIZE_FLOAT 8

#define IC_INDEX_ZERO 0
#define IC_COUNT 1

#define IC_INPUT_QUIT_SIGNAL 1
#define IC_INPUT_NO_EVENT_SIGNAL 0

#define IC_WINDOW_MAX_FPS 60.0f

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned const char ucchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef const float cfloat;
typedef const char cchar;
typedef char byte;

#endif /* core_h */
