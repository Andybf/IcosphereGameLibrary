//
//  DebugCamera.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef DebugCamera_hpp
#define DebugCamera_hpp

#include "Camera.hpp"
#include "Inputs.hpp"

class DebugCamera {
    
private:
    
    Camera* camera;
    struct Mouse {
        float x;
        float y;
        bool isRightPressed;
        bool isLeftPressed;
    } actualMouseState, lastMouseState;
    
    float yaw;
    float pitch;
    
public:
    DebugCamera(Camera* camera);
    
    void handleMousePress(short buttonPressed, short actionPerformed);
    void handleMouseMovement(float x, float y);
    void handleMouseScroll(float x, float y);
};

#endif /* DebugCamera_hpp */
