//
//  StanfordObj.hpp
//  IcosphereGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//
//  Additional Information:
//  PLY is a computer file format known as the Polygon File Format or the
//  Stanford Triangle Format. It was principally designed to store
//  three-dimensional data from 3D scanners.

#pragma once

#include "ModelData.hpp"
#include "../../Core.hpp"

#define AP_PLY_MAGIC "ply"
#define AP_PLY_MAGIC_BUFFER_SIZE 4

#define AP_PLY_FORMAT "format"
#define AP_PLY_ELEMENT "element"
#define AP_PLY_COMMENT "comment"
#define AP_PLY_PROPERTY "property"
#define AP_PLY_END_HEADER "end_header\n"

#define AP_PLY_FORMAT_ASCII "ascii 1.0\n"
#define AP_PLY_FORMAT_B_LITTLE_ENDIAN "binary_little_endian 1.0\n"
#define AP_PLY_FORMAT_B_BIG_ENDIAN "binary_big_endian 1.0\n"
#define AP_PLY_FORMAT_BUFFER_SIZE 32

#define AP_PLY_ELEMENT_VERTEX "vertex"
#define AP_PLY_ELEMENT_FACE "face"
#define AP_PLY_ELEMENT_BUFFER_SIZE 10

#define AP_PLY_MAX_VECTOR_DIMENSIONS 9

#define AP_PLY_HEADER_LINE_SIZE 128

namespace StanfordObj {
    
    ModelData* extractFrom(FILE* file);
    
};
