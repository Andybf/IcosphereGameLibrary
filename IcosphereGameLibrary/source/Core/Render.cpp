//
//  render.c
//  Icosphere
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include <Icosphere/Core/Render.hpp>

struct ContextInformation {
    char* glVendor;
    char* glRenderer;
    char* glVersion;
    char* glExtensions;
} contextInfo;

SDL_GLContext glContext;

void saveContextInformation();
void renderLoop();


void Render::initialize(Window::WindowData* window) {
    glContext = SDL_GL_CreateContext(window->sdlWindow);
    window->renderCallback = renderLoop;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    saveContextInformation();
}

void Render::renderLoop() {
    IC_TEST(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Render::drawElementsInstanced(struct Entity* model, uint count) {
    IC_TEST(glDrawElementsInstanced(model->modelDrawType,
                                    model->mesh->indicesSize,
                                    GL_UNSIGNED_INT,
                                    0,
                                    count));
}

void Render::drawElements(struct Entity* model) {
    IC_TEST(glDrawElements(model->modelDrawType,
                           model->mesh->indicesSize,
                           GL_UNSIGNED_INT,
                           0));
}

void Render::drawArrays(struct Entity* model) {
    IC_TEST(glDrawArrays(model->modelDrawType,
                         IC_INDEX_ZERO,
                         (float)model->mesh->verticesSize/model->mesh->dimensions));
}

void saveContextInformation() {
    contextInfo.glVendor     = (char*)glGetString(GL_VENDOR);
    contextInfo.glRenderer   = (char*)glGetString(GL_RENDERER);
    contextInfo.glVersion    = (char*)glGetString(GL_VERSION);
    contextInfo.glExtensions = (char*)glGetString(GL_EXTENSIONS);
    Render::printContextInformation();
}

void Render::printContextInformation() {
    printf("Apolo-SDL-OpenGL Context Information:\nglVendor   : %s\nglRenderer : %s\nglVersion  : %s\n\n",
            contextInfo.glVendor,
            contextInfo.glRenderer,
            contextInfo.glVersion
    );
}
