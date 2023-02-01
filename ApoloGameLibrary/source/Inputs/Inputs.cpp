//
//  Inputs.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 31/01/23.
//

#include <Apolo/Inputs/Inputs.hpp>

SDL_Event sdlEvent;
uint8_t isQuitSignalEmitted;
struct Keyboard keyboard;

void setKeyUpCallbackFunction(void* (*callback)(int)) {
    keyboard.respondKeyUp = callback;
}
void setKeyDownCallbackFunction(void* (*callback)(int)) {
    keyboard.respondKeyDown = callback;
}

struct Mouse mouse;

void Input::setMouseMovementCallbackFunction(void (*callback)(double, double)) {
    mouse.respondMovement = callback;
}
void Input::setMouseDownCallbackFunction(void (*callback)(int button, int x, int y)) {
    mouse.respondClickDown = callback;
}
void Input::setMouseUpCallbackFunction(void (*callback)(int button, int x, int y)) {
    mouse.respondClickUp = callback;
}
void Input::setMouseScrollCallbackFunction(void (*callback)(double, double)) {
    mouse.respondScroll = callback;
}

void Input::receiveInputFromSdl() {
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_KEYUP:
                if (AP_IS_FUNCTION_DEFINED(keyboard.respondKeyUp)) {
                    keyboard.respondKeyUp(sdlEvent.key.keysym.sym);
                }
                break;
            case SDL_KEYDOWN:
                if (AP_IS_FUNCTION_DEFINED(keyboard.respondKeyDown)) {
                    keyboard.respondKeyDown(sdlEvent.key.keysym.sym);
                }
                break;
            case SDL_MOUSEMOTION:
                if (AP_IS_FUNCTION_DEFINED(mouse.respondMovement)) {
                    mouse.respondMovement(sdlEvent.motion.x, sdlEvent.motion.y);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(AP_IS_FUNCTION_DEFINED(mouse.respondClickUp)) {
                    mouse.respondClickUp(sdlEvent.button.button, sdlEvent.button.x, sdlEvent.button.y);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(AP_IS_FUNCTION_DEFINED(mouse.respondClickDown)) {
                    mouse.respondClickDown(sdlEvent.button.button, sdlEvent.button.x, sdlEvent.button.y);
                }
                break;
            case SDL_MOUSEWHEEL:
                if(AP_IS_FUNCTION_DEFINED(mouse.respondScroll)) {
                    mouse.respondScroll(sdlEvent.motion.x, sdlEvent.motion.y);
                }
                break;
            case SDL_QUIT:
                isQuitSignalEmitted = true;
            default:
                break;
        }
    }
}

uint8_t Input::shouldExitProgram() {
    return isQuitSignalEmitted;
}
