//
//  Camera.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Core.hpp"

class Camera {
    
private:
    glm::mat4 matrix;
    
    glm::vec3 position;
    glm::vec3 upAxis;
    glm::vec3 orientation;
    
public:
    Camera();
    
    glm::mat4 getMatrix();
    
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    
    void setOrientation(float yaw, float pitch);
    glm::vec3 getOrientation();
};

#endif /* Camera_hpp */
