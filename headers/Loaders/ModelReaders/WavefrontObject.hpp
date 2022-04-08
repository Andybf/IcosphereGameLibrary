//
//  WavefrontObjectReader.h
//  MinervaEngine
//
//  Created by Anderson on 27/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//

#pragma once

#include "Core.hpp"
#include "../../Loaders/ModelReaders/ModelData.hpp"

class WavefrontObj {

private:
    static void readFaceValue(char* buffer, std::vector<uint>* indices, FILE* file);
    static void moveFilePointerToBefore(FILE* file, cchar* substring);
    static void readVertexes(FILE* file, cchar* vertexName, std::vector<float>* vertexList);
    static void readFaces(FILE* file,std::vector<uint>* vertIndices);
    static void resolveVectorIndices(std::vector<uint>& normalIndices);
    
public:
    static void process(FILE* file, ModelData* modelData);
};
