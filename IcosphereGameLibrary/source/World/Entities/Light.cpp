//
//  Light.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Icosphere/World/Entities/Light.hpp>

Light::Light() {
    this->isSourceObjectVisible = false;
    this->color = glm::vec3(1);
}