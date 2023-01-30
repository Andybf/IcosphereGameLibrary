//
//  ModelLoader.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#pragma once

#include "FileLoader.hpp"
#include "../World/Entity.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Mesh.hpp"
#include "./ModelReaders/StanfordObject.hpp"
#include "../Loaders/ModelReaders/ModelData.hpp"

namespace ModelLoader {

    Mesh* load(cchar* modelFileName, uint shaderId);
    void checkModelData(ModelData* modelData, cchar* modelName);
};

