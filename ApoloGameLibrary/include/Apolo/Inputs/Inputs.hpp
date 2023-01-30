//
//  Inputs.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Inputs_hpp
#define Inputs_hpp

#define AP_MOUSE_BUTTON_RIGHT 0
#define AP_MOUSE_RELEASE 0

struct Keyboard {
    void* (*respondKeyPress)(int buttonPressed, int actionPerformed);
};

struct Mouse {
    void* (*respondClickPress)(int buttonPressed, int actionPerformed);
    void* (*respondMovement)(double xpos, double ypos);
    void* (*respondScroll)(double xpos, double ypos);
};

#endif /* Inputs_h */
