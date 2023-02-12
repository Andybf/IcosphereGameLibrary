//
//  Inputs.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Inputs_hpp
#define Inputs_hpp

#include "../Core.hpp"

namespace Input {
    void setKeyUpCallbackFunction(void (*callback)(int));
    void setKeyDownCallbackFunction(void (*callback)(int));

    void setMouseMovementCallbackFunction(void (*callback)(double, double));
    void setMouseDownCallbackFunction(void (*callback)(int button, int x, int y));
    void setMouseUpCallbackFunction(void (*callback)(int button, int x, int y));
    void setMouseScrollCallbackFunction(void (*callback)(double, double));

    void receiveInputFromSdl();
    uint8_t shouldExitProgram();
}

struct Keyboard {
    void (*respondKeyUp)(int keyPressed);
    void (*respondKeyDown)(int keyPressed);
};

struct Mouse {
    void (*respondClickUp)(int button, int x, int y);
    void (*respondClickDown)(int button, int x, int y);
    void (*respondMovement)(double xpos, double ypos);
    void (*respondScroll)(double xpos, double ypos);
};

#endif /* Inputs_h */
