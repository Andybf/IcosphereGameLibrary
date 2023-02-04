//
//  window.c
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include <Apolo/Core/Window.hpp>
#include <Apolo/Inputs/Inputs.hpp>

struct ProgramTime {
    int current = 0;
    int elapsed = 0;
    int delta = 0;
    int currentSecond = 0;
    float frameCounter = 0;
    float fps = 0;
} programTime;

Window::WindowData* window;
void windowLoopCallback();

void Window::exitWindow() {
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
    exit(0);
}

float Window::getFrameRate() {
    return programTime.fps;
}

struct Window::WindowData* Window::getWindowData() {
    return window;
}

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
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
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
    emscripten_set_main_loop(windowLoopCallback, AP_WINDOW_MAX_FPS, 1);
#else
    SDL_GL_SetSwapInterval(1);
    while(! Input::shouldExitProgram() ) {
        windowLoopCallback();
    }
    Window::exitWindow();
#endif
    
}

void windowLoopCallback() {
    programTime.elapsed = SDL_GetTicks();
    programTime.delta = programTime.elapsed - programTime.current;
    
    Input::receiveInputFromSdl();
    window->renderCallback();
    window->clientLoopCallback();
    
    programTime.frameCounter++;
    programTime.currentSecond += programTime.delta;
    if (programTime.currentSecond >= 1000) {
        programTime.currentSecond = 0;
        programTime.fps = programTime.frameCounter;
        programTime.frameCounter = 0;
    }
    
    SDL_GL_SwapWindow(window->sdlWindow);
    
    programTime.current = programTime.elapsed;
}
