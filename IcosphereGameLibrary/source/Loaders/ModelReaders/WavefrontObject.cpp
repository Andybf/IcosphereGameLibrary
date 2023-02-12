//
//  WavefrontObject.cpp
//  Icosphere
//
//  Created by Anderson Bucchianico on 30/01/23.
//
//  Additional Information:
//  OBJ (or .OBJ) is a geometry definition file format first developed by
//  Wavefront Technologies for its Advanced Visualizer animation package.

#include <Icosphere/Loaders/ModelReaders/WavefrontObject.hpp>

void readFaceValue(char* buffer, std::vector<uint>* indices, FILE* file);
void moveFilePointerToBefore(FILE* file, cchar* substring);
void readVertexes(FILE* file, cchar* vertexName, std::vector<float>* vertexList);
void readFaces(FILE* file,std::vector<uint>* vertIndices);
void resolveVectorIndices(std::vector<uint>& normalIndices);

void WavefrontObj::process(FILE* file, ModelData* modelData) {
    fseek(file, 0, SEEK_SET);
    readVertexes(file, "v ", &modelData->vertices.data);
    readVertexes(file, "vn ", &modelData->normals.data);
    readVertexes(file, "vt ", &modelData->texCoords.data);
    readFaces(file, &modelData->indices.data);
}

void readVertexes(FILE* file, cchar* name, std::vector<float>* vertexes) {
    moveFilePointerToBefore(file, name);
    char* buffer = (char*)calloc(sizeof(char),10);
    int vertexNameSize = (int)strlen(name);
    fread(buffer, vertexNameSize, 1, file);
    while(strcmp(buffer, name) == 0) {
        int index = -1;
        do {
            index++;
            buffer[index] = fgetc(file);
            if (buffer[index] == 'e') {
                fseek(file, +4, SEEK_CUR);
            }
            if (buffer[index] == ' ') {
                vertexes->push_back(atof(buffer));
                index = -1;
            }
        } while(buffer[index] != '\n');
        vertexes->push_back(atof(buffer));
        memset(&buffer[0], 0, sizeof(buffer));
        fread(buffer, vertexNameSize, 1, file);
    }
    free(buffer);
    fseek(file, ftell(file)-vertexNameSize, SEEK_SET);
}

void readFaces(FILE* file, std::vector<uint>* vertIndices) {
    moveFilePointerToBefore(file, (cchar*)"f ");
    char* buffer = (char*) calloc(sizeof(char), 5);
    while (fgetc(file) == 'f' && fgetc(file) == ' ') {
        char readChar = NULL;
        while(readChar != '\n' && readChar != EOF) {
            readFaceValue(buffer, vertIndices, file);
            fseek(file, -1, SEEK_CUR);
            readChar = fgetc(file);
        }
    }
    free(buffer);
    fseek(file, ftell(file)-2, SEEK_SET);
}

void readFaceValue(char* buffer, std::vector<uint>* indices, FILE* file) {
    char readChar = fgetc(file);
    int x=0;
    while(readChar >= '0' && readChar <='9' ) {
        buffer[x] = readChar;
        readChar = fgetc(file);
        x++;
    }
    if (x > 0) {
        indices->push_back(atof(buffer)-1);
        memset(&buffer[0], 0, sizeof(buffer));
    }
}

void moveFilePointerToBefore(FILE* file, cchar* substring) {
    short bufferSize = 32;
    char* buffer = (char*) calloc(sizeof(char), bufferSize+1);
    long offset = -1;
    long originalPosition = ftell(file);
    while(offset < 0 && fgetc(file) != EOF) {
        fseek(file, -1, SEEK_CUR);
        fread(buffer, bufferSize, sizeof(char), file);
        offset = strstr(buffer, substring) - buffer;
    }
    if (fgetc(file) == EOF) {
        fseek(file, originalPosition, SEEK_SET);
    } else {
        fseek(file, -(strlen(buffer)-offset)-1, SEEK_CUR);
    }
    free(buffer);
}
