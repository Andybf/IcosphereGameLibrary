//
//  render.c
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include "../include/Apolo/Core/Render.hpp"

struct ContextInformation {
    char* glVendor;
    char* glRenderer;
    char* glVersion;
    char* glExtensions;
} contextInfo;

SDL_GLContext glContext;
ushort frameCount;
float framesPerSecond;
void (*callbackLoop)();

void saveContextInformation();
void renderLoop();


void Render::initialize(SDL_Window* sdlWindow, void (*callbackFunctionLoop)()) {
    glContext = SDL_GL_CreateContext(sdlWindow);
    callbackLoop = callbackFunctionLoop;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    saveContextInformation();
    
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(renderLoop, 0, 1);
#else
    while(1) {
        renderLoop();
    }
#endif
}

void renderLoop() {
    AP_TEST(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    callbackLoop();
}

void Render::drawElementsInstanced(struct Entity* model, uint count) {
    AP_TEST(glDrawElementsInstanced(model->modelDrawType, model->mesh->indicesSize, GL_UNSIGNED_INT, 0, count));
}
void Render::drawElements(struct Entity* model) {
    AP_TEST(glDrawElements(model->modelDrawType, model->mesh->indicesSize, GL_UNSIGNED_INT, 0));
}
void Render::drawArrays(struct Entity* model) {
    AP_TEST(glDrawArrays(model->modelDrawType, AP_INDEX_ZERO, (float)model->mesh->verticesSize/3));
}

void resetFrameCount() {
    frameCount = 0;
    //glfwSetTime(0.0);
}

int Render::getFrameCount() {
    return frameCount;
}

float Render::getFramesPerSecond() {
    return framesPerSecond;
}

void saveContextInformation() {
    contextInfo.glVendor     = (char*)glGetString(GL_VENDOR);
    contextInfo.glRenderer   = (char*)glGetString(GL_RENDERER);
    contextInfo.glVersion    = (char*)glGetString(GL_VERSION);
    contextInfo.glExtensions = (char*)glGetString(GL_EXTENSIONS);
    printf("%s\n", Render::getContextInformation());
}

char* Render::getContextInformation() {
    char* string = (char*) malloc(sizeof(char*)*256);
    sprintf(string, "Apolo-SDL-OpenGL Context Information:\nglVendor   : %s\nglRenderer : %s\nglVersion  : %s\n\n",
            contextInfo.glVendor,
            contextInfo.glRenderer,
            contextInfo.glVersion
           );
    return string;
}
