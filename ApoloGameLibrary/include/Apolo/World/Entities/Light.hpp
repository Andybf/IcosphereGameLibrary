//
//  Light.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Light_hpp
#define Light_hpp

#include "Entity.hpp"

class Light : public Entity {
    
private:
       
public:
    bool isSourceObjectVisible;
    glm::vec3 color;
    
    Light();
};


#endif /* Light_hpp */
