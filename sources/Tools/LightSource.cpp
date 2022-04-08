//
//  LightSource.cpp
//  MinervaEngine
//
//  Created by Anderson on 25/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//

#include "LightSource.hpp"

LightSource::LightSource() {
    this->isSourceObjectVisible = false;
    this->color = glm::vec3(1);
}
