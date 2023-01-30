//
//  Projection.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Projection_hpp
#define Projection_hpp

#include "../Core.hpp"

class Projection {
    
private:
    glm::mat4 orthographicMatrix;
    glm::mat4 perspectiveMatrix;
    
    float fieldOfView;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    
public:
    Projection();
    
    glm::mat4 getOrthographic();
    void setOrthographic(float west, float east, float south, float north);
    
    glm::mat4 getPerspective();
    void setPerspecProjection(float fieldOfView, float aspectRatio, float nearPlane, float FarPlane);
    
    float getFieldOfView();
    void setFieldOfView(float fieldOfView);
    
    float getNearPlane();
    void setNearPlane(float nearPlane);
    
    float getFarPlane();
    void setFarPlane(float farPlane);
};


#endif /* Projection_hpp */
