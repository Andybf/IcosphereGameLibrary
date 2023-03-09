//
//  ModelLoader.cpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include "./ModelLoader.hpp"

void checkModelData(ModelData* modelData, cchar* modelName);

Mesh* ModelLoader::loadFromFile(cchar* modelFileName, uint shaderId) {
    char* objectSourcePath = (char*)calloc(sizeof(char),256);
    FileLoader::generatePathForFile(objectSourcePath ,"objects", modelFileName);
    FILE* file = fopen(objectSourcePath, "rb");
    if (file == NULL) {
        printf("[AP_MDL_ERROR] File cannot be found: %s\n",objectSourcePath);
        exit(1);
    }
    free(objectSourcePath);
    
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData),1);
    if (strstr(modelFileName, ".ply")) {
        modelData = StanfordObj::extractFrom(file);
    } else {
        WavefrontObj::process(file, modelData);
    }
    fclose(file);
    checkModelData(modelData, modelFileName);
    
    return ModelLoader::loadFromModelData(modelData, shaderId);
}

Mesh* ModelLoader::loadFromModelData(ModelData* modelData, uint relatedShaderId) {
    ulong modelsSize = modelData->vertices.data.size()*sizeof(GLfloat);
    ulong colorsSize = modelsSize + modelData->colors.data.size()*sizeof(GLfloat);
    ulong normalsSize = colorsSize + modelData->normals.data.size()*sizeof(GLfloat);
    
    Mesh* mesh = (Mesh*)calloc(sizeof(Mesh), 1);
    mesh->vboId = VBO::generateNewVBO(modelData->vertices.data,
                                      modelData->colors.data,
                                      modelData->normals.data,
                                      modelData->texCoords.data);
    mesh->vaoId = VAO::generateNewVAO();
    VAO::bind(mesh->vaoId);
    
    VAO::linkAttribute(mesh->vaoId,
                       glGetAttribLocation(relatedShaderId,"positionVec"),
                       modelData->vertices.dimensions,
                       0);
    if (glGetAttribLocation(relatedShaderId, "colors") != -1) {
        VAO::linkAttribute(mesh->vaoId,
                           glGetAttribLocation(relatedShaderId, "colors"),
                           modelData->colors.dimensions,
                           modelsSize);
    }
    if (glGetAttribLocation(relatedShaderId, "normals") != -1) {
        VAO::linkAttribute(mesh->vaoId,
                           glGetAttribLocation(relatedShaderId, "normals"),
                           modelData->normals.dimensions,
                           colorsSize);
    }
    if (glGetAttribLocation(relatedShaderId, "texCoord") != -1) {
        VAO::linkAttribute(mesh->vaoId,
                           glGetAttribLocation(relatedShaderId, "texCoord"),
                           modelData->texCoords.dimensions,
                           normalsSize);
    }
    
    if (modelData->indices.data.size() > 0) {
        mesh->eboId = EBO::generateNewEBO(&modelData->indices.data);
        mesh->indicesSize = (uint)modelData->indices.data.size();
    } else {
        mesh->verticesSize = (uint)modelData->vertices.data.size();
    }
    mesh->dimensions = modelData->vertices.dimensions;
    free(modelData);
    VAO::unbind();
    VBO::unbind();
    EBO::unbind();
    
    return mesh;
}

void checkModelData(ModelData* modelData, cchar* modelName) {
    if (modelData->vertices.data.size() <= 0) {
        printf("[AP_MDL_ERROR] The model %s does not contain any vertices.\n",
               modelName);
        exit(1);
    }
    if (modelData->indices.data.size() <= 0) {
        printf("[AP_MDL_ERROR] The model %s does not contain any indices.\n",
               modelName);
        exit(1);
    }
}
