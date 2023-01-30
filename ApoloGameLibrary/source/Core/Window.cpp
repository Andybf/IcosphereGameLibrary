//
//  window.c
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#include "../include/Apolo/Core/Window.hpp"

struct WindowData {
    char* title;
    uint16_t width;
    uint16_t height;
    float aspectRatio;
    SDL_Window* sdlWindow;
    SDL_Event sdlEvent;
} *window;

void Window::initialize(ushort width, ushort height, char* title) {
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Init( SDL_INIT_VIDEO );
    
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
                                         SDL_WINDOW_OPENGL
    );
}

void Window::exit() {
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
}

SDL_Window* Window::getSdlWindow() {
    return window->sdlWindow;
}

SDL_Event* Window::getSdlWindowEvent() {
    return &window->sdlEvent;
}
