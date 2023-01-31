//
//  window.c
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include <Apolo/Core/Window.hpp>

Window::WindowData* window;
void windowLoopCallback();

void Window::initialize(ushort width, ushort height, char* title) {
    
    SDL_Init( SDL_INIT_VIDEO );
    
#ifndef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif
    
    window = (struct WindowData*) malloc(sizeof(struct WindowData*));
    window->width = width;
    window->height = height;
    window->title = (char*)calloc(sizeof(char),128);
    strcpy(window->title, title);
    window->sdlWindow = SDL_CreateWindow(
        window->title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window->width,
        window->height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
}

void Window::setLoopCallback(void (*mainLoop)()) {
    window->clientLoopCallback = mainLoop;
}

void Window::startLoop() {
    
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(windowLoopCallback, 0, 1);
    #else
        while(1) {
            windowLoopCallback();
        }
    #endif
    
}

void windowLoopCallback() {
    if (SDL_PollEvent(&window->sdlEvent)) {
        if (window->sdlEvent.type == SDL_KEYUP) {
            printf("keyup\n");
        }
        if (SDL_QUIT == window->sdlEvent.type) {
            Window::exit();
        }
    }
    
    window->renderCallback();
    window->clientLoopCallback();
}


void Window::exit() {
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
}

struct Window::WindowData* Window::getWindowData() {
    return window;
}
