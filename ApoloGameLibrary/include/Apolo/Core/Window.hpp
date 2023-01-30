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
    void initialize(ushort width, ushort height, char* title);

    void exit();

    SDL_Window* getSdlWindow();

    SDL_Event* getSdlWindowEvent();
}

#endif /* window_h */
