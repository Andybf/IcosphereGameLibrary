//
//  ModelCreator.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 09/02/23.
//

#include <Apolo/Tools/ModelCreator.hpp>

ModelData* ModelCreator::grid(uint width, uint height, float squareSize) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);

    modelData->vertices.dimensions = 3;
    for (float x=0; x<=width; x++) {
        for (float z=0; z<=height; z++){
            modelData->vertices.data.insert(modelData->vertices.data.end(),{
                x*squareSize, 0.0f, z*squareSize,
            });
        }
    }
    for (int j=0; j<width; j++) {
        for (int i=0; i<height; i++) {
            uint row1 = j * (height + 1);
            uint row2 = (j + 1) * (height + 1);
            modelData->indices.data.insert(modelData->indices.data.end(), {
                row1+i, row1+i+1, row2+i,
                row1+i, row2+i+1, row2+i
            });
        }
    }
    modelData->indices.data.insert(modelData->indices.data.end(), {
        height, (uint)(modelData->vertices.data.size()-3)/3, height,
    });
    return modelData;
}

ModelData* ModelCreator::surface(float width, float height) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);
    return modelData;
}

ModelData* ModelCreator::sphere(float radius) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);
    return modelData;
}

ModelData* ModelCreator::cube(float size) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);
    return modelData;
}
