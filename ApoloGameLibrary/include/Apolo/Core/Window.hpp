//
//  window.h
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#ifndef window_h
#define window_h

#include "../Core.hpp"

namespace Window {

    struct WindowData {
        char* title;
        uint16_t width;
        uint16_t height;
        float aspectRatio;
        SDL_Window* sdlWindow;
        SDL_Event sdlEvent;
        void (*clientLoopCallback)();
        void (*renderCallback)();
    };

    void initialize(ushort width, ushort height, char* title);

    void setLoopCallback(void (*mainLoop)());

    void startLoop();

    void exitWindow();

    struct WindowData* getWindowData();
}

#endif /* window_h */
