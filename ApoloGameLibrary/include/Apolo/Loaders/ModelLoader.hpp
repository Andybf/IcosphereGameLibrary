//
//  ModelLoader.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#pragma once

#include "FileLoader.hpp"
#include "../World/Entity.hpp"
#include "../Core/VBO.hpp"
#include "../Core/VAO.hpp"
#include "../Core/EBO.hpp"
#include "../Core/Mesh.hpp"
#include "./ModelReaders/StanfordObject.hpp"
#include "../Loaders/ModelReaders/ModelData.hpp"

namespace ModelLoader {

    Mesh* load(cchar* modelFileName, uint shaderId);
};

