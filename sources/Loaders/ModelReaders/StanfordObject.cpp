//
//  StanfordObject.cpp
//  MinervaEngine
//
//  Created by Anderson on 29/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.

#include "StanfordObj.hpp"

ModelData* StanfordObj::extractFrom(FILE* file) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData),1);
    StanfordObj::checkFileType(file);
    StanfordObj::checkFormat(file);
    uint64_t vertices = StanfordObj::getNumberOf(MI_PLY_ELEMENT_VERTEX, file);
    
    cchar* coordinateNames[9] = { "x","y","z", "nx","ny","nz", "s","t","r"};
    char* buffer = (char*) calloc(sizeof(char), MI_PLY_HEADER_LINE_SIZE);
    uint8_t vecDimensions[3] = {0,0,0};
    for (uint8_t v=0; v<9; v++) {
        fgets(buffer, MI_PLY_HEADER_LINE_SIZE, file);
        if ((strstr(buffer, coordinateNames[v]) - buffer) > 0) {
            vecDimensions[v/3] += 1;
        } else {
            fseek(file, -strlen(buffer), SEEK_CUR);
            break;
        }
    }
    free(buffer);
    uint8_t numVertices = vecDimensions[0];
    uint8_t numNormals =  vecDimensions[1];
    uint8_t numTexCoords =  vecDimensions[2];
    uint64_t faces = StanfordObj::getNumberOf(MI_PLY_ELEMENT_FACE, file);
    StanfordObj::moveFilePointerToAfter(MI_PLY_END_HEADER, file);
    
    float* floatBuffer = (float*)calloc(sizeof(float),3);
    for (int y=0; y<vertices; y++) {
        fread(floatBuffer, numVertices, sizeof(float), file);
        modelData->vertices.insert(modelData->vertices.end(), floatBuffer, floatBuffer+numVertices);
        
        fread(floatBuffer, numNormals, sizeof(float), file);
        modelData->normals.insert(modelData->normals.end(), floatBuffer, floatBuffer+numNormals);
        
        fread(floatBuffer, numTexCoords, sizeof(float), file);
        modelData->texCoords.insert(modelData->texCoords.end(), floatBuffer, floatBuffer+numTexCoords);
    }
    free(floatBuffer);
    StanfordObj::readFaces(file, faces, &modelData->indices);
    return modelData;
}

void StanfordObj::readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices) {
    short facesPerRow = fgetc(file);
    uint* uintBuffer = (uint*)calloc(sizeof(uint), facesPerRow);
    for (int x=0; x<faces; x++) {
        fread(uintBuffer, facesPerRow, sizeof(uint), file);
        indices->insert(indices->end(), uintBuffer, uintBuffer+facesPerRow);
        fseek(file, +1, SEEK_CUR);
    }
    free(uintBuffer);
}

void StanfordObj::checkFileType(FILE* file) {
    char* buffer = (char*) calloc(sizeof(char), MI_PLY_MAGIC_BUFFER_SIZE);
    fseek(file, 0x0, SEEK_SET);
    if (strcmp(fgets(buffer, MI_PLY_MAGIC_BUFFER_SIZE, file), MI_PLY_MAGIC) != 0) {
        printf("[MI_PLY_ERROR] file format is not .ply\n");
        free(buffer);
        fclose(file);
        exit(1);
    }
    free(buffer);
}

void StanfordObj::checkFormat(FILE* file) {
    char* format = (char*) calloc(sizeof(char), MI_PLY_FORMAT_BUFFER_SIZE);
    fseek(file, 11, SEEK_SET);
    if (strcmp(fgets(format, MI_PLY_FORMAT_BUFFER_SIZE, file), MI_PLY_FORMAT_B_LITTLE_ENDIAN) != 0) {
        printf("[MI_PLY_ERROR] file data is not on the binary little endian format.\n");
        free(format);
        fclose(file);
        exit(1);
    }
    free(format);
}

unsigned int StanfordObj::getNumberOf(const char* elementName, FILE* file) {
    StanfordObj::moveFilePointerToAfter(MI_PLY_ELEMENT, file);
    StanfordObj::moveFilePointerToAfter(elementName, file);
    char* buffer = (char*) calloc(sizeof(char), MI_PLY_ELEMENT_BUFFER_SIZE);
    int bufferPosition = 0;
    while ((buffer[bufferPosition] = fgetc(file)) != '\n') {
        bufferPosition++;
    }
    uint result = atoi(buffer);
    free(buffer);
    return result;
}

void StanfordObj::moveFilePointerToAfter(const char* substring, FILE* file) {
    char* buffer = (char*) calloc(sizeof(char), MI_PLY_HEADER_LINE_SIZE);
    long originalPosition = ftell(file);
    long offset = -1;
    while (offset < 0 && !feof(file)) {
        fgets(buffer, MI_PLY_HEADER_LINE_SIZE, file);
        offset = strstr(buffer, substring) - buffer;
    }
    if (feof(file)) {
        fseek(file, originalPosition, SEEK_SET);
    } else {
        fseek(file, -(strlen(buffer)-offset)+strlen(substring), SEEK_CUR);
    }
    free(buffer);
}
