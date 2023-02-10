//
//  ModelCreator.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 09/02/23.
//

#ifndef ModelCreator_hpp
#define ModelCreator_hpp

#include "../Core.hpp"
#include "../Loaders/ModelReaders/ModelData.hpp"

namespace ModelCreator {

    ModelData* grid(uint width, uint height, float squareSize);

    ModelData* surface(float width, float height);

    ModelData* sphere(float radius);

    ModelData* cube(float size);
}

#endif /* ModelCreator_hpp */
