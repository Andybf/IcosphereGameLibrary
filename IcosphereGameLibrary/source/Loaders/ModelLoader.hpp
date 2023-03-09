//
//  ModelLoader.hpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include "FileLoader.hpp"
#include "../World/Entity.hpp"
#include "../Core/VBO.hpp"
#include "../Core/VAO.hpp"
#include "../Core/EBO.hpp"
#include "../Core/Mesh.hpp"
#include "./ModelReaders/StanfordObject.hpp"
#include "./ModelReaders/WavefrontObject.hpp"
#include "../Loaders/ModelReaders/ModelData.hpp"

namespace ModelLoader {

    Mesh* loadFromFile(cchar* modelFileName, uint shaderId);
    Mesh* loadFromModelData(ModelData* modelData, uint shaderId);
};

#endif /* ModelLoader_hpp */
