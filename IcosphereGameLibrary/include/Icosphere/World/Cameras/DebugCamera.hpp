//
//  DebugCamera.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef DebugCamera_hpp
#define DebugCamera_hpp

#include "../Camera.hpp"

class DebugCamera {
    
private:
    
    Camera* camera;
    struct Mouse {
        float x;
        float y;
        bool isActivationButtonPressed;
        bool isLeftPressed;
    } actualMouseState, lastMouseState;
    
    float yaw;
    float pitch;
    
public:
    DebugCamera(Camera* camera);
    
    void handleMouseClickUp();
    void handleMouseClickDown();
    void handleMouseMovement(float x, float y);
    void handleMouseScroll(float x, float y);
};

#endif /* DebugCamera_hpp */
