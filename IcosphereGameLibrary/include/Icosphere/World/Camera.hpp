//
//  Camera.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "../Core.hpp"

class Camera {
    
private:
    glm::mat4 matrix;
    
    glm::vec3 position;
    glm::vec3 upAxis;
    glm::vec3 orientation;
    glm::vec3 rotationCenter;
    
public:
    Camera();
    
    glm::mat4 getMatrix();
    
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    
    void setAngleOrientation(float angle, glm::vec3 orientation);
    void setOrientation(float yaw, float pitch);
    glm::vec3 getOrientation();
    
    void setRotationCenter(glm::vec3 lookPoint);
};

#endif /* Camera_hpp */
