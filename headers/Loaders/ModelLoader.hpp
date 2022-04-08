//
//  ModelLoader.hpp
//  MinervaEngine
//
//  Created by Anderson on 16/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//

#pragma once

#include "FileLoader.hpp"
#include "../World/Entity.hpp"
#include "../Core/VBO.hpp"
#include "../Core/VAO.hpp"
#include "../Core/EBO.hpp"
#include "../Core/Mesh.h"
#include "./ModelReaders/StanfordObj.hpp"
#include "../Loaders/ModelReaders/ModelData.hpp"

class ModelLoader {
    
private:
        
public:
    static Mesh* load(cchar* modelFileName, uint shaderId);
    static void checkModelData(ModelData* modelData, cchar* modelName);
};

