//
//  ModelCreator.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 09/02/23.
//

#include "./ModelCreator.hpp"

ModelData* ModelCreator::grid(uint width, uint height, float squareSize) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);
    
    // Generate Vertices =================================================
    
    modelData->vertices.dimensions = 3;
    int counterStart = 0;
    int counterLimit = width;
    for (int z=0; z<height; z++) {
        for (int x=counterStart; x<=counterLimit; x++) {
            modelData->vertices.data.insert(modelData->vertices.data.end(),{
                abs((float)x), 0.0f, (float)z,
                abs((float)x), 0.0f, (float)z+1
            });
        }
        if (z != height-1) {
            modelData->vertices.data.insert(modelData->vertices.data.end(),{
                abs((float)counterLimit), 0.0f, (float)z+2
            });
        }
        counterLimit = (counterLimit==0) ? width : 0;
        counterStart = (counterStart==0 || counterStart==1) ? -(width-1) : 1;
    }
    
    // Generate Indices ==================================================
    
    for (int verticeIndex=0; verticeIndex<modelData->vertices.data.size(); verticeIndex+=3) {
        int faceIndex = 0;
        for (int verticeToCompareIndex=0; verticeToCompareIndex<verticeIndex; verticeToCompareIndex+=3) {
            if (modelData->vertices.data.at(verticeIndex) == modelData->vertices.data.at(verticeToCompareIndex) &&
                modelData->vertices.data.at(verticeIndex+2) == modelData->vertices.data.at(verticeToCompareIndex+2))
            {
                break;
            }
            faceIndex++;
        }
        modelData->indices.data.push_back(faceIndex);
    }
    
    return modelData;
}

ModelData* ModelCreator::quad(float width, float height) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData), 1);
    modelData->vertices.dimensions = 3;
    modelData->vertices.data.insert(modelData->vertices.data.end(), {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    });
    modelData->texCoords.dimensions = 2;
    modelData->texCoords.data.insert(modelData->texCoords.data.end(), {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    });
    modelData->indices.data.insert(modelData->indices.data.end(), {
        0, 1, 2,
        0, 2, 3
    });
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
