//
//  StanfordObject.hpp
//  MinervaEngine
//
//  Created by Anderson on 29/03/22.
//  Copyright © 2022 Anderson Bucchianico. All rights reserved.
//  Additional Information:
//  PLY is a computer file format known as the Polygon File Format or the
//  Stanford Triangle Format. It was principally designed to store
//  three-dimensional data from 3D scanners.

#pragma once

#include "ModelData.hpp"
#include "Core.hpp"

#define MI_PLY_MAGIC "ply"
#define MI_PLY_MAGIC_BUFFER_SIZE 4

#define MI_PLY_FORMAT "format"
#define MI_PLY_ELEMENT "element"
#define MI_PLY_COMMENT "comment"
#define MI_PLY_PROPERTY "property"
#define MI_PLY_END_HEADER "end_header\n"

#define MI_PLY_FORMAT_ASCII "ascii 1.0\n"
#define MI_PLY_FORMAT_B_LITTLE_ENDIAN "binary_little_endian 1.0\n"
#define MI_PLY_FORMAT_B_BIG_ENDIAN "binary_big_endian 1.0\n"
#define MI_PLY_FORMAT_BUFFER_SIZE 32

#define MI_PLY_ELEMENT_VERTEX "vertex"
#define MI_PLY_ELEMENT_FACE "face"
#define MI_PLY_ELEMENT_BUFFER_SIZE 10

#define MI_PLY_HEADER_LINE_SIZE 128

class StanfordObj {
    
public:
    static ModelData* extractFrom(FILE* file);
    
private:
    static void readFaces(FILE* file, uint64_t faces, std::vector<uint>* indices);
    
    static void checkFileType(FILE* file);
    static void checkFormat(FILE* file);
    static uint getNumberOf(cchar* elementName, FILE* file);
    
    static void moveFilePointerToAfter(cchar* substring, FILE* file);
};
