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
//

#include <Apolo/Loaders/ModelReaders/StanfordObject.hpp>

void readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices);
void checkFileType(FILE* file);
void checkFormat(FILE* file);
uint getNumberOf(cchar* elementName, FILE* file);
void moveFilePointerToAfter(cchar* substring, FILE* file);
void getVectorDimensionsInFile(ModelData* modelData, FILE* file);

ModelData* StanfordObj::extractFrom(FILE* file) {
    ModelData* modelData = (ModelData*) calloc(sizeof(ModelData),1);
    checkFileType(file);
    checkFormat(file);
    uint64_t vertexesCount = getNumberOf(AP_PLY_ELEMENT_VERTEX, file);
    getVectorDimensionsInFile(modelData, file);
    uint64_t faces = getNumberOf(AP_PLY_ELEMENT_FACE, file);
    moveFilePointerToAfter(AP_PLY_END_HEADER, file);
    
    float* floatBuffer = (float*)calloc(sizeof(float),3);
    for (int y=0; y<vertexesCount; y++) {
        fread(floatBuffer, modelData->vertices.dimensions, sizeof(float), file);
        modelData->vertices.data.insert(modelData->vertices.data.end(),
                                        floatBuffer,
                                        floatBuffer+modelData->vertices.dimensions);
        
        fread(floatBuffer, modelData->normals.dimensions, sizeof(float), file);
        modelData->normals.data.insert(modelData->normals.data.end(),
                                       floatBuffer,
                                       floatBuffer+modelData->normals.dimensions);
        
        fread(floatBuffer, modelData->texCoords.dimensions, sizeof(float), file);
        modelData->texCoords.data.insert(modelData->texCoords.data.end(),
                                         floatBuffer,
                                         floatBuffer+modelData->texCoords.dimensions);
    }
    free(floatBuffer);
    readFaces(file, faces, &modelData->indices.data);
    return modelData;
}

void readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices) {
    short facesPerRow = fgetc(file);
    uint* uintBuffer = (uint*)calloc(sizeof(uint), facesPerRow);
    if (facesPerRow == 3) {
        for (int x=0; x<faces; x++) {
            fread(uintBuffer, facesPerRow, sizeof(uint), file);
            indices->insert(indices->end(), uintBuffer, uintBuffer+facesPerRow);
            fseek(file, +1, SEEK_CUR);
        }
    } else if (facesPerRow == 4) {
        for (int x=0; x<faces; x++) {
            fread(uintBuffer, facesPerRow, sizeof(uint), file);
            uint triangleFanIndices[6] = {
                uintBuffer[0],uintBuffer[1],uintBuffer[2],
                uintBuffer[0],uintBuffer[2],uintBuffer[3]
            };
            indices->insert(indices->end(), triangleFanIndices, 6+triangleFanIndices);
            fseek(file, +1, SEEK_CUR);
        }
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

void getVectorDimensionsInFile(ModelData* modelData, FILE* file) {
    cchar* coordinateNames[9] = { "x","y","z", "nx","ny","nz", "s","t","r"};
    char* buffer = (char*) calloc(sizeof(char), AP_PLY_HEADER_LINE_SIZE);
    uint8_t vectorDimensionsList[3] = {0,0,0};
    for (uint8_t v=0; v<AP_PLY_MAX_VECTOR_DIMENSIONS; v++) {
        fgets(buffer, AP_PLY_HEADER_LINE_SIZE, file);
        if ((strstr(buffer, coordinateNames[v]) - buffer) > 0) {
            vectorDimensionsList[v/3] += 1;
        } else {
            fseek(file, -strlen(buffer), SEEK_CUR);
            break;
        }
    }
    modelData->vertices.dimensions = vectorDimensionsList[0];
    modelData->normals.dimensions = vectorDimensionsList[1];
    modelData->texCoords.dimensions = vectorDimensionsList[2];
    free(buffer);
}
