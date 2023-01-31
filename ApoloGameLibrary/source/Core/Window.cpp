//
//  window.c
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include <Apolo/Core/Window.hpp>

struct ProgramTime {
    int current = 0;
    int elapsed = 0;
    int delta = 0;
} programTime;

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
    
    window = (struct WindowData*) malloc(sizeof(struct WindowData));
    window->width = width;
    window->height = height;
    window->aspectRatio = (float) width/height;
    window->title = (char*)calloc(sizeof(char),128);
    strcpy(window->title, title);
    window->sdlWindow = SDL_CreateWindow(
        window->title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window->width,
        window->height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
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
            Window::exitWindow();
        }
    }
    
    programTime.elapsed = SDL_GetTicks();
    programTime.delta = programTime.elapsed - programTime.current;
    if (programTime.delta > 1000/10.0f) {
        
        window->renderCallback();
        window->clientLoopCallback();
        programTime.current = programTime.elapsed;
    }
    SDL_Delay(16.6);
}


void Window::exitWindow() {
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
    exit(0);
}

struct Window::WindowData* Window::getWindowData() {
    return window;
}
