//
//  FileLoader.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/Loaders/FileLoader.hpp>

char* programPath;
void removeExecutableNameFrom(std::string* path);

void FileLoader::setProgramSystemPath(std::string path) {
    removeExecutableNameFrom(&path);
    programPath = (char*)calloc(sizeof(char),256);
    strcpy(programPath, path.c_str());
}

void removeExecutableNameFrom(std::string* path) {
    for (ushort x = path->size()-1; x > 0; x--) {
        if (path->at(x) == '/' || path->at(x) == '\\') {
            path = &path->replace(x, path->size(), "\0");
            break;
        }
    }
}

void FileLoader::generatePathForFile(char* sourcePath, cchar* folder, cchar* filename) {
    sprintf(sourcePath, "%s%s%s%s%s", programPath,MI_OS_PATH_FORMAT,folder,MI_OS_PATH_FORMAT,filename);
}

char* FileLoader::read(char* sourcePath) {
    FILE* file = fopen(sourcePath, "r");
    if(file == NULL) {
        printf("[AP_FLD_ERROR] No such file has been found: %s\n",sourcePath);
        exit(1);
    }
    struct stat fileInfo;
    stat(sourcePath, &fileInfo);
    
    char* fileSource = (char*) calloc(sizeof(char), fileInfo.st_size);
    fread(fileSource, fileInfo.st_size-1, 1, file);
    
    if (strlen(fileSource) < 1) {
        printf("[AP_FLD_WARN] File is empty:: %s\n",sourcePath);
    }
    return fileSource;
}
