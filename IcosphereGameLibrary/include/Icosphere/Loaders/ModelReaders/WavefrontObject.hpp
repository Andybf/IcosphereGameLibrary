//
//  WavefrontObject.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//
//  Additional Information:
//  OBJ (or .OBJ) is a geometry definition file format first developed by
//  Wavefront Technologies for its Advanced Visualizer animation package.

#pragma once

#include "../../Core.hpp"
#include "../../Loaders/ModelReaders/ModelData.hpp"

namespace WavefrontObj {

    void process(FILE* file, ModelData* modelData);
};
