//
//  Icosphere.hpp
//  IcosphereGameLibrary
//
//  This is the public header file, all the declaratives here are meant for client use.
//
//  Created by Anderson Bucchianico on 13/02/23.
//

#ifndef Icosphere_h
#define Icosphere_h

// C includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// C++ includes
#include <vector>
#include <string>

// GLM
#include "../dependencies/glm/glm.hpp"
#include "../dependencies/glm/gtx/euler_angles.hpp"
#include "../dependencies/glm/gtx/matrix_decompose.hpp"
#include "../dependencies/glm/gtc/random.hpp"
#include "../dependencies/glm/gtx/rotate_vector.hpp"
#include "../dependencies/glm/gtc/noise.hpp"

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

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned const char ucchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef const float cfloat;
typedef const char cchar;
typedef char byte;

struct Mesh {
    uint vboId;
    uint vaoId;
    uint eboId;
    uint indicesSize;
    uint verticesSize;
    ushort dimensions;
};

// WORLD Modules ==============================================================

class Entity {
private:
    glm::mat4 matrix;
public:
    Entity();
    
    bool isEnabled;
    
    ushort textureType;
    ushort modelDrawType;
    ushort relatedShaderId;
    ushort relatedTextureId;
    Mesh* mesh;

    glm::mat4 getMatrix();

    void setScale(glm::vec3 scale);
    glm::vec3 getScale();
    
    void setPosition(glm::vec3 position);
    void addToPosition(glm::vec3 position);
    glm::vec3 getPosition();
    
    void setOrientation(float angle,glm::vec3 orientation);
    glm::vec3 getOrientation();
};

class Text : public Entity {
private:
    float characterScale;
    ushort fontmapWidth;
    int* string32bit;
    std::vector<glm::vec2> stringPositionList;
    uint stringSize;
    void calcCharPositionOnScreen(uchar* string);
public:
    char * content;
    Text(uint fontMapTextureId, uint textShaderId);
    void processContents(uchar* string);
    int* get32bitString();
    uint getStringSize();
    std::vector<glm::vec2> getStringPositionList();
};

class Light : public Entity {
    
private:
       
public:
    bool isSourceObjectVisible;
    glm::vec3 color;
    
    Light();
};

class Camera {
private:
    glm::mat4 matrix;
    glm::vec3 position;
    glm::vec3 upAxis;
    glm::vec3 orientation;
    glm::vec3 rotationCenter;
public:
    Camera();
    
    glm::mat4 getMatrix();
    
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    
    void setAngleOrientation(float angle, glm::vec3 orientation);
    void setOrientation(float yaw, float pitch);
    glm::vec3 getOrientation();
    
    void setRotationCenter(glm::vec3 lookPoint);
};

class Projection {
private:
    glm::mat4 orthographicMatrix;
    glm::mat4 perspectiveMatrix;
    
    float fieldOfView;
    float aspectRatio;
    float nearPlane;
    float farPlane;
public:
    Projection();
    
    glm::mat4 getOrthographic();
    void setOrthographic(float west, float east, float south, float north);
    
    glm::mat4 getPerspective();
    void setPerspecProjection(float fieldOfView, float aspectRatio, float nearPlane, float FarPlane);
    
    float getFieldOfView();
    void setFieldOfView(float fieldOfView);
    
    float getNearPlane();
    void setNearPlane(float nearPlane);
    
    float getFarPlane();
    void setFarPlane(float farPlane);
};

class DebugCamera {
private:
    Camera* camera;
    struct Mouse {
        float x;
        float y;
        bool isActivationButtonPressed;
        bool isLeftPressed;
    } actualMouseState, lastMouseState;
    
    float yaw;
    float pitch;
public:
    DebugCamera(Camera* camera);
    void handleMouseClickUp();
    void handleMouseClickDown();
    void handleMouseMovement(float x, float y);
    void handleMouseScroll(float x, float y);
};

// CORE Modules ================================================================

namespace Window {
    struct WindowData {
        char* title;
        uint16_t width;
        uint16_t height;
        float aspectRatio;
        SDL_Window* sdlWindow;
    };
    void exitWindow();
    void initialize(ushort width, ushort height, char* title);
    float getFrameRate();
    struct WindowData* getWindowData();
    void setLoopCallback(void (*mainLoop)());
    void startLoop();
}

namespace Render {
    void drawArrays(struct Entity* model);
    void drawElements(struct Entity* model);
    void drawElementsInstanced(struct Entity* model, uint count);
    void initialize(Window::WindowData* window);
    void printContextInformation();
}

namespace Shader {
    void setActiveProgram(uint shaderId);
    uint getActiveShaderId();
    void setUniformModelViewProjection(Entity* entity, glm::mat4 camera, glm::mat4 projection);
    void setUniformModelProjection(Entity* entity, glm::mat4 projection);
    void setUniformTexture(uint textureId, uint dimensions);
    void setUniformIntArray(cchar* name, int* intArray, int size);
    void setUniformFloat(cchar* name, float value);
    void setUniformVec2Array(cchar* name, const float* value, int size);
    void setUniformVec3(cchar* name, glm::vec3 value);
}

// Loaders Module ==============================================================

struct ModelData {
    struct Vertices {
        std::vector<float> data;
        unsigned int dimensions;
    } vertices;
    
    struct Colors {
        std::vector<float> data;
        unsigned int dimensions;
    } colors;
    
    struct Normals {
        std::vector<float> data;
        unsigned int dimensions;
    } normals;
    
    struct TexCoords {
        std::vector<float> data;
        unsigned int dimensions;
    } texCoords;
    
    struct Indices {
        std::vector<unsigned int> data;
    } indices;
};

namespace FileLoader {
    void setProgramSystemPath(std::string programPath);
    char* read(char* sourcePath);
};

namespace ModelLoader {
    Mesh* loadFromFile(cchar* modelFileName, uint shaderId);
    Mesh* loadFromModelData(ModelData* modelData, uint shaderId);
};

namespace ShaderLoader {
    GLuint load(cchar* vertexFileName, cchar* fragmentFileName);
};

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

// INPUTS Module ===============================================================

namespace Input {
    void setKeyUpCallbackFunction(void (*callback)(int));
    void setKeyDownCallbackFunction(void (*callback)(int));

    void setMouseMovementCallbackFunction(void (*callback)(double, double));
    void setMouseDownCallbackFunction(void (*callback)(int button, int x, int y));
    void setMouseUpCallbackFunction(void (*callback)(int button, int x, int y));
    void setMouseScrollCallbackFunction(void (*callback)(double, double));

    void setWindowEventResizeCallbackFunction(void (*callback)(int newWidth, int newHeight));
}

// TOOLS Module ================================================================

namespace ModelCreator {
    ModelData* grid(uint width, uint height, float squareSize);
    ModelData* quad(float width, float height);
    ModelData* sphere(float radius);
    ModelData* cube(float size);
}

#endif /* Icosphere_h */
