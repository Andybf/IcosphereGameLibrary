//
//  Entity.h
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Entity_h
#define Entity_h

#include "../Core/Mesh.hpp"
#include "../Core.hpp"

class Entity {
        
private:

    glm::mat4 matrix;

public:

    Entity();
    
    bool isEnabled;
    
    ushort textureType;
    ushort modelDrawType;
    ushort relatedShaderId;
    ushort relatedTextureId;
    Mesh* mesh;

    glm::mat4 getMatrix();

    void setScale(glm::vec3 scale);
    glm::vec3 getScale();
    
    void setPosition(glm::vec3 position);
    void addToPosition(glm::vec3 position);
    glm::vec3 getPosition();
    
    void setOrientation(float angle,glm::vec3 orientation);
    glm::quat getOrientation();
};


#endif /* Entity_h */
