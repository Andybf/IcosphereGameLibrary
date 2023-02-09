//
//  ModelData.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#pragma once

#include <vector>

struct ModelData {
    struct Vertices {
        std::vector<float> data;
        unsigned int dimensions;
    } vertices;
    
    struct Normals {
        std::vector<float> data;
        unsigned int dimensions;
    } normals;
    
    struct TexCoords {
        std::vector<float> data;
        unsigned int dimensions;
    } texCoords;
    
    struct Indices {
        std::vector<unsigned int> data;
    } indices;
};
