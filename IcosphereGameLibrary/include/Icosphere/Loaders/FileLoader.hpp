//
//  FileLoader.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef FileLoader_hpp
#define FileLoader_hpp

#ifdef _WIN32
    #define MI_OS_PATH_FORMAT "\\" //for Windows based system
#else
    #define MI_OS_PATH_FORMAT "/" //for Unix-like system
#endif

#include "../Core.hpp"
#include <iostream>

namespace FileLoader {
        
    void generatePathForFile(char* sourcePath, cchar* folder, cchar* fileName);
    void setProgramSystemPath(std::string programPath);
    char* read(char* sourcePath);
    
};

#endif /* FileLoader_hpp */
