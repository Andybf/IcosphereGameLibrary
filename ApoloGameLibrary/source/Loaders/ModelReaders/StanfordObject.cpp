//
//  StanfordObject.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//
//  Additional Information:
//  PLY is a computer file format known as the Polygon File Format or the
//  Stanford Triangle Format. It was principally designed to store
//  three-dimensional data from 3D scanners.

#include "StanfordObject.hpp"

void readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices);
void checkFileType(FILE* file);
void checkFormat(FILE* file);
uint getNumberOf(cchar* elementName, FILE* file);
void moveFilePointerToAfter(cchar* substring, FILE* file);


ModelData* StanfordObj::extractFrom(FILE* file) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData),1);
    checkFileType(file);
    checkFormat(file);
    uint64_t vertices = getNumberOf(AP_PLY_ELEMENT_VERTEX, file);
    
    cchar* coordinateNames[9] = { "x","y","z", "nx","ny","nz", "s","t","r"};
    char* buffer = (char*) calloc(sizeof(char), AP_PLY_HEADER_LINE_SIZE);
    uint8_t vecDimensions[3] = {0,0,0};
    for (uint8_t v=0; v<9; v++) {
        fgets(buffer, AP_PLY_HEADER_LINE_SIZE, file);
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
    uint64_t faces = getNumberOf(AP_PLY_ELEMENT_FACE, file);
    moveFilePointerToAfter(AP_PLY_END_HEADER, file);
    
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
    readFaces(file, faces, &modelData->indices);
    return modelData;
}

void readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices) {
    short facesPerRow = fgetc(file);
    uint* uintBuffer = (uint*)calloc(sizeof(uint), facesPerRow);
    for (int x=0; x<faces; x++) {
        fread(uintBuffer, facesPerRow, sizeof(uint), file);
        indices->insert(indices->end(), uintBuffer, uintBuffer+facesPerRow);
        fseek(file, +1, SEEK_CUR);
    }
    free(uintBuffer);
}

void checkFileType(FILE* file) {
    char* buffer = (char*) calloc(sizeof(char), AP_PLY_MAGIC_BUFFER_SIZE);
    fseek(file, 0x0, SEEK_SET);
    if (strcmp(fgets(buffer, AP_PLY_MAGIC_BUFFER_SIZE, file), AP_PLY_MAGIC) != 0) {
        printf("[AP_PLY_ERROR] file format is not .ply\n");
        free(buffer);
        fclose(file);
        exit(1);
    }
    free(buffer);
}

void checkFormat(FILE* file) {
    char* format = (char*) calloc(sizeof(char), AP_PLY_FORMAT_BUFFER_SIZE);
    fseek(file, 11, SEEK_SET);
    if (strcmp(fgets(format, AP_PLY_FORMAT_BUFFER_SIZE, file), AP_PLY_FORMAT_B_LITTLE_ENDIAN) != 0) {
        printf("[AP_PLY_ERROR] file data is not on the binary little endian format.\n");
        free(format);
        fclose(file);
        exit(1);
    }
    free(format);
}

unsigned int getNumberOf(const char* elementName, FILE* file) {
    moveFilePointerToAfter(AP_PLY_ELEMENT, file);
    moveFilePointerToAfter(elementName, file);
    char* buffer = (char*) calloc(sizeof(char), AP_PLY_ELEMENT_BUFFER_SIZE);
    int bufferPosition = 0;
    while ((buffer[bufferPosition] = fgetc(file)) != '\n') {
        bufferPosition++;
    }
    uint result = atoi(buffer);
    free(buffer);
    return result;
}

void moveFilePointerToAfter(const char* substring, FILE* file) {
    char* buffer = (char*) calloc(sizeof(char), AP_PLY_HEADER_LINE_SIZE);
    long originalPosition = ftell(file);
    long offset = -1;
    while (offset < 0 && !feof(file)) {
        fgets(buffer, AP_PLY_HEADER_LINE_SIZE, file);
        offset = strstr(buffer, substring) - buffer;
    }
    if (feof(file)) {
        fseek(file, originalPosition, SEEK_SET);
    } else {
        fseek(file, -(strlen(buffer)-offset)+strlen(substring), SEEK_CUR);
    }
    free(buffer);
}
