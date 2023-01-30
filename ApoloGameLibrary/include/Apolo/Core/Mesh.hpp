//
//  Mesh.h
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Mesh_h
#define Mesh_h

#include "../Core.hpp"

struct Mesh {
    uint vboId;
    uint vaoId;
    uint eboId;
    uint indicesSize;
    uint verticesSize;
};

#endif /* Mesh_h */
