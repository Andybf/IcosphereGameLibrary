//
//  ModelLoader.cpp
//  MinervaEngine
//
//  Created by Anderson on 16/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//

#include "ModelLoader.hpp"

Mesh* ModelLoader::load(cchar* modelFileName, uint relatedShaderId) {
    char* objectSourcePath = (char*)calloc(sizeof(char),256);
    FileLoader::generatePathForFile(objectSourcePath ,"objects", modelFileName);
    FILE* file = fopen(objectSourcePath, "rb");
    if (file == NULL) {
        printf("[MI_MDL_ERROR] No such file has been found: %s\n",objectSourcePath);
        exit(1);
    }
    free(objectSourcePath);
    
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData),1);
    modelData = StanfordObj::extractFrom(file);
    fclose(file);
    ModelLoader::checkModelData(modelData,modelFileName);
    
    ulong modelsSize = modelData->vertices.size()*sizeof(GLfloat);
    ulong normalsSize = modelsSize + modelData->normals.size()*sizeof(GLfloat);
    
    Mesh* mesh = (Mesh*)calloc(sizeof(Mesh), 1);
    mesh->vboId = VBO::generateNewVBO(modelData->vertices,modelData->normals,modelData->texCoords);
    mesh->vaoId = VAO::generateNewVAO();
    VAO::bind(mesh->vaoId);
    VAO::linkAttribute(mesh->vaoId, glGetAttribLocation(relatedShaderId, "positionVec"), MI_VECTORS_XYZ, 0);
    VAO::linkAttribute(mesh->vaoId, glGetAttribLocation(relatedShaderId, "normals" ), MI_NORMALS_IJK,  modelsSize);
    VAO::linkAttribute(mesh->vaoId, glGetAttribLocation(relatedShaderId, "texCoord"), MI_TEXCOORD_STR, normalsSize);
    if (modelData->indices.size() > 0) {
        EBO::generateNewEBO(&modelData->indices);
        mesh->indicesSize = (uint)modelData->indices.size();
    } else {
        mesh->verticesSize = (uint)modelData->vertices.size();
    }
    free(modelData);
    VAO::unbind();
    VBO::unbind();
    EBO::unbind();
    
    return mesh;
}

void ModelLoader::checkModelData(ModelData* modelData, cchar* modelName) {
    if (modelData->vertices.size() <= 0) {
        printf("[MI_MDL_ERROR] The model %s does not contain any vertices.\nWe can't continue, exiting...\n",modelName);
        exit(1);
    }
    if (modelData->indices.size() <= 0) {
        printf("[MI_MDL_ERROR] The model %s does not contain any indices.\nWe can't continue, exiting...\n",modelName);
        exit(1);
    }
}
